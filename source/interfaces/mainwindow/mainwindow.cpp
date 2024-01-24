#include "mainwindow.h"
#include <ui_mainwindow.h>

#include <services/theme-loader/theme_loader.h>

#include <QDebug>
#include "../../services/image-downloader/image_downloader.h"

const QString DATABASE_FILE = "./database/database.db";

const QSizeF dimensionFactor(1.686 * 1.15, 1.481 * 1.15);

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui_(std::make_unique<Ui::MainWindow>()),
          settings_manager_("mainwindow"),
          database_(settings_manager_.GetSettings().database) {
    ui_->setupUi(this);

    this->setStyleSheet(Theme::Load(settings_manager_.GetSettings().theme));

    ui_->screen->addAction(ui_->copy);
    ui_->screen->addAction(ui_->save_image);
    ui_->screen->addAction(ui_->image_scale_up);
    ui_->screen->addAction(ui_->image_scale_down);

    log_.info("Starting...");

    if (!database_.connect()) {
        qDebug() << "DatabaseModel is not opened" << endl;
        // TODO(Pavel): Добавить диалоговое окно
    }
    log_.info("DatabaseModel initialized");

    table_model_ = std::make_unique<QSqlTableModel>(this, database_.db);
    table_model_->setTable(database_.schema + ".clients");
    table_model_->select();
    table_model_->sort(0, Qt::SortOrder::AscendingOrder);

    log_.info("DatabaseModel table_model_ initialized");

    connect(table_model_.get(), SIGNAL(dataChanged(
                                               const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(database_table_view_data_changed(
                               const QModelIndex&)));

    ui_->database_table_view->setModel(table_model_.get());
    ui_->database_table_view->setColumnHidden(0, true);
    log_.info("DatabaseModel table_model_ set to table");

    if (!ImageDownloader::FetchImage(
            "./resources/images/image.png",
            settings_manager_.GetSettings().image.url
    )) {
        qDebug() << "Downloading failed" << endl;
        // TODO(Pavel): Добавить диалоговое окно
    }

    QImage image;

    if (!image.load("./resources/images/image.png")) {
        assert(false);
    }

    text_painter_.SetImage(
            image
    );

    for (int i = 0; i < 3; ++i) {
        items_[i].options = settings_manager_.GetSettings().font_settings[i];
    }

    for (const auto &item: items_) {
        text_painter_.DrawText(item);
    }

    current_image_size_ = default_image_size_ = text_painter_.GetOriginalImage().size();

    ui_->progress_bar->setVisible(false);

    ui_->screen->setPixmap(text_painter_.GetResultPixmap());

    log_.info("Initializing done!");
}

MainWindow::~MainWindow() {
    log_.info("Closed!");
}

void MainWindow::on_copy_triggered() {
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setImage(text_painter_.GetResultImage(), QClipboard::Clipboard);
    ui_->statusbar->showMessage("Картинка успешно скопирована в буфер обмена!");
    log_.info("Image successfully copied");
}

void MainWindow::on_settings_triggered() {
//    Options window(&settings);
//    window.exec();
//    apply();
    TextPositionSelector().exec();
    settings_manager_.ReloadSettings();
    for (int i = 0; i < 3; ++i) {
        items_[i].options.position = settings_manager_.GetSettings().font_settings[i].position;
    }
    ReDrawImage();
    ui_->statusbar->showMessage("Настройки сохранены!");
    log_.info("Settngs saved");
}

void MainWindow::on_save_image_triggered() {
    if (settings_manager_.GetSettings().output_folder == "default") {
        ui_->statusbar->showMessage("Изображение не сохранено! Добавьте путь к папке с результатом!");
        return;
    }
    text_painter_.GetResultImage().save(
            settings_manager_.GetSettings().output_folder
            + "/image_"
            + items_[0].content
            + ".jpg"
    );
    ui_->statusbar->showMessage("image_"
                                + items_[0].content
                                + " успешно сохранена!");
}

void MainWindow::on_print_triggered() {
    /*log_.info("Print triggered");
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::NativeFormat);
    printer.setPrinterName("EPSON L3210 Series");
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Rejected) {
        log_.info("Printer rejected");
        return;
    }
    log_.info("Print started");
    QPainter painter(&printer);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QModelIndexList selectedList = ui->database_table_view_->selectionModel()->selectedRows();

    if (!selectedList.empty()) {
        int intervalX = 0, intervalY = -(image_.height() * dimensionFactor.height() - 100);
        for (int i = 0; i < selectedList.size(); i++) {

            log_.info("Image " + std::to_string(i) + " printed!");

            if (i % 12 == 0 && i != 0) {
                printer.newPage();
                intervalY = -(image_.height() * dimensionFactor.height() - 100);
                intervalX = 0;
            }

            items[0] = QString::fromStdString(std::to_string(selectedList[i].row() + 1));
            items[1] = table_model_->index(selectedList[i].row(), 0).data().toString();
            items[2] = table_model_->index(selectedList[i].row(), 1).data().toString();
            draw();

            table_model_->setData(
                    table_model_->index(
                            selectedList[i].row(),
                            2
                    ),
                    "Распечатан"
            );

            if (i % 2 == 0) {
                intervalY += image_.height() * dimensionFactor.height() + 100;
                intervalX = 0;
            }

            painter.drawPixmap(150 + intervalX, 150 + intervalY, image_.width() * dimensionFactor.width(),
                               image_.height() * dimensionFactor.height(),
                               QPixmap::fromImage(*image_));
            intervalX += image_.width() * dimensionFactor.width() + 100;
        }
    } else {
        table_model_->setData(
                table_model_->index(selectedList[0].row(), 3),
                "Распечатан"
        );
        painter.drawPixmap(150, 150, image_.width() * dimensionFactor.width(),
                           image_.height() * dimensionFactor.height(), QPixmap::fromImage(*image_));
    }
    painter.end();*/
}

void MainWindow::on_database_table_view_clicked(const QModelIndex &index) {
    log_.info("On table clicked");
    SetContents(index);
    ReDrawImage();
}

void MainWindow::on_database_search_textChanged() {
    log_.info("Searching " + ui_->database_search->text().toStdString());
    for (int i = 0; i <= table_model_->rowCount(); i++) {
        for (int j = 0; j <= table_model_->columnCount(); j++) {
            if (table_model_->index(i, j).data().toString().contains(ui_->database_search->text())) {
                log_.info("Found: " + table_model_->index(i, j).data().toString().toStdString());
                if (ui_->database_table_view->isRowHidden(i)) ui_->database_table_view->showRow(i);
                break;
            } else {
                if (!ui_->database_table_view->isRowHidden(i)) ui_->database_table_view->hideRow(i);
            }
        }
    }
}

void MainWindow::on_show_database_triggered() {
    log_.info("DatabaseModel visible: true");
    ui_->database_dock->setVisible(true);
}

void MainWindow::on_hide_database_triggered() {
    log_.info("DatabaseModel visible: false");
    ui_->database_dock->setVisible(false);
}

void MainWindow::on_show_image_triggered() {
    log_.info("Image visible: true");
    ui_->database_dock->setVisible(true);
}

void MainWindow::on_hide_image_triggered() {
    log_.info("Image visible: false");
    ui_->database_dock->setVisible(false);
}

void MainWindow::on_image_scale_up_triggered() {
    log_.info("Image scaled up");
    current_image_size_.setWidth(current_image_size_.width() + 50);
    current_image_size_.setHeight(current_image_size_.height() + 50);
    ReDrawImage();
}

void MainWindow::on_image_scale_down_triggered() {
    log_.info("Image scaled down");
    current_image_size_.setWidth(current_image_size_.width() - 50);
    current_image_size_.setHeight(current_image_size_.height() - 50);
    ReDrawImage();
}

void MainWindow::on_save_some_items_triggered() {
    /*log_.info("Save some items triggered!");
    unsigned amount;
    log_.info("Records amount dialog opened!");
    RecordsAmmount dialog(&amount);
    if (dialog.exec() == QDialog::Rejected) {
        log_.info("Rejected!");
        return;
    }
    log_.info("Accepted! Ammount: " + std::to_string(amount));
    QList<int> list;
    log_.info("Cells: ");
    for (int i = 0; i < table_model_->rowCount() && list.size() < amount; ++i) {
        if (table_model_->index(i, 0).data().toString().isEmpty() &&
            table_model_->index(i, 1).data().toString().isEmpty()) {
            list.push_back(i);
            log_.info(i);
        }
    }
    ui->progressBar->setMaximum(amount);
    int maximum = amount;
    ui->progressBar->setVisible(true);
    if (list.isEmpty()) {
        log_.warn("List is empty!");
        return;
    }
    log_.info("Inserting data: ");
    while (amount--) {
        if (list.isEmpty()) break;
        QSqlRecord record = table_model_->record();
        record.setValue("Name", items[1]);
        record.setValue("Phone", items[2]);
        record.setValue("Status", " ");
        record.setValue("Number", table_model_->index(list.first(), 3).data().toString());
        log_.info("    Record: " + std::to_string(list.first()) + " " + items[1].toStdString() + " " +
                   items[2].toStdString());
        table_model_->setRecord(list.first(), record);
        list.pop_front();
        ui->progressBar->setValue((maximum - (amount + 1)) % maximum);
    }
    ui->progressBar->setVisible(false);
    table_model_->submitAll();
    ui->statusbar->showMessage("Запись успешно довалена!");
    log_.info("Save some items end!");*/
}

void MainWindow::on_save_some_images_triggered() {
    log_.info("Save some images triggered!");
    QModelIndexList selected_rows = ui_->database_table_view->selectionModel()->selectedRows();
    if (selected_rows.empty()) {
        ui_->statusbar->showMessage("Вы не выделили строки!");
        return;
    }

    if (settings_manager_.GetSettings().output_folder == "default") {
        ui_->statusbar->showMessage("Изображения не сохранены! Добавьте путь к папке с результатом!");
        return;
    }

    ui_->progress_bar->setMaximum(selected_rows.size());
    ui_->progress_bar->setVisible(true);

    int progress_index = 0;
    for (const auto &selected_row: selected_rows) {
        ui_->progress_bar->setValue(progress_index);
        QCoreApplication::processEvents();

        SetContents(selected_row);

        text_painter_.Clear();
        for (const auto &item: items_) {
            text_painter_.DrawText(item);
        }

        if (text_painter_.GetResultImage().save(settings_manager_.GetSettings().output_folder
                                                + "/image_"
                                                + items_[0].content
                                                + ".jpg"
        )) {
            ui_->statusbar->showMessage("image_"
                                        + items_[0].content
                                        + " успешно сохранена!");
            ++progress_index;
        } else {
            ui_->statusbar->showMessage("image_"
                                        + items_[0].content
                                        + " не сохранена!");
        }
    }

    if (progress_index != selected_rows.size()) {
        ui_->statusbar->showMessage("Не все изображения были сохранены!");
        return;
    }

    ui_->statusbar->showMessage("Все изображения были успешно сохранены!");

    ui_->progress_bar->setVisible(false);
}

void MainWindow::ReDrawImage() {
    text_painter_.Clear();
    for (const auto &item: items_) {
        text_painter_.DrawText(item);
    }
    ui_->screen->setPixmap(text_painter_.GetResultPixmap().scaled(current_image_size_, Qt::KeepAspectRatioByExpanding));
}

void MainWindow::database_table_view_data_changed(const QModelIndex &index) {
    table_model_->submit();
    table_model_->select();
    SetContents(index);
    ReDrawImage();
}

void MainWindow::on_refresh_database_action_triggered() {
    table_model_->select();
}

void MainWindow::on_insert_single_record_triggered() {
    table_model_->insertRows(table_model_->rowCount(), 1);
    table_model_->submit();
}

void MainWindow::on_insert_same_records_triggered() {
    // TODO(Pavel): Добавить диалоговое окно
}

void MainWindow::SetContents(const QModelIndex &index) {
    for (int i = 0; i < 3; ++i) {
        items_[i].content = table_model_->index(index.row(), i).data().toString();
    }
}
