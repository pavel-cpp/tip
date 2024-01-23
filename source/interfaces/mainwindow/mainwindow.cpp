#include "mainwindow.h"
#include <ui_mainwindow.h>

#include <services/theme-loader/theme_loader.h>

#include <QDebug>
#include "../../services/image-downloader/image_downloader.h"

const QString DATABASE_FILE = "./database/database.db";

const QSizeF dimensionFactor(1.686 * 1.15, 1.481 * 1.15);

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui_(std::make_unique<Ui::MainWindow>()), settings_manager_(),
          database_(settings_manager_.GetSettings().database) {
    ui_->setupUi(this);

    this->setStyleSheet(Theme::Load(settings_manager_.GetSettings().theme));

    connect(&context_action_copy_, SIGNAL(triggered()), this, SLOT(on_copy_triggered()));
    context_menu_.addAction(&context_action_copy_);

    log_.info("Starting...");

    if (!database_.connect()) {
        qDebug() << "DatabaseModel is not opened" << endl;
        // TODO(Pavel): Добавить диалоговое окно
    }
    log_.info("DatabaseModel initialized");

    table_model_ = std::make_unique<QSqlTableModel>(this, database_.db);
    table_model_->setTable(database_.schema + ".clients");
    table_model_->select();

    log_.info("DatabaseModel table_model_ initialized");

    connect(table_model_.get(), SIGNAL(dataChanged(
                                               const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(on_database_table_view_data_changed(
                               const QModelIndex&)));

    ui_->database_table_view->setModel(table_model_.get());
    ui_->database_table_view->setColumnHidden(0, true);
    log_.info("DatabaseModel table_model_ set to table");

    if (!ImageDownloader::FetchImage(
            "./resources/images/image.png",
            settings_manager_.GetSettings().image.url
    )) {
        qDebug() << "Downloading failed" << endl;
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

void MainWindow::on_screen_customContextMenuRequested(const QPoint &pos) {
    log_.info("Context context_menu_ requested");
    context_menu_.popup(ui_->screen->mapToGlobal(pos));
}

void MainWindow::on_settings_triggered() {
//    Options window(&settings);
//    window.exec();
//    apply();
    ui_->statusbar->showMessage("Настройки сохранены!");
    log_.info("Settngs saved");
}

void MainWindow::on_save_image_triggered() {
    text_painter_.GetResultImage().save(
            settings_manager_.GetSettings().output_folder
            + "image_"
            + items_[0].content
            + ".jpg"
    );
//    log_.info("Image_"
//               + items[0].toStdString()
//               + " successfully saved!");
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
    for (int i = 0; i < 3; ++i) {
        items_[i].content = table_model_->index(index.row(), i).data().toString();
    }
    ReDrawImage();
}

void MainWindow::on_database_search_textChanged() {
    log_.info("Searching " + ui_->database_search->toPlainText().toStdString());
    for (int i = 0; i <= table_model_->rowCount(); i++) {
        for (int j = 0; j <= table_model_->columnCount(); j++) {
            if (table_model_->index(i, j).data().toString().contains(ui_->database_search->toPlainText())) {
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
//    log_.info("Save some images triggered!");
//    QModelIndexList selectedList = ui->database_table_view_->selectionModel()->selectedRows();
//    if (!selectedList.empty()) {
//        ui->progressBar->setMaximum(selectedList.size());
//        int maximum = selectedList.size();
//        ui->progressBar->setVisible(true);
//        for (int i = 0; i < selectedList.size(); i++) {
//            QCoreApplication::processEvents();
//            ui->progressBar->setValue((i + 1) % maximum);
//
//            items[0] = QString::fromStdString(std::to_string(selectedList[i].row() + 1));
//            items[1] = table_model_->index(selectedList[i].row(), 0).data().toString();
//            items[2] = table_model_->index(selectedList[i].row(), 1).data().toString();
//            draw();
//
//            image_.save(settings.fileOut
//                        + "\\editing_image_"
//                        + items[0]
//                        + ".jpg"
//            );
//            ui->statusbar->showMessage("Image_"
//                                       + items[0]
//                                       + " успешно сохранена!");
//            log_.info("    Image_"
//                       + items[0].toStdString()
//                       + " saved successfully!");
//        }
//    }
//
//    ui->progressBar->setVisible(false);
//    log_.info("Save some images end!");
}

void MainWindow::ReDrawImage() {
    text_painter_.Clear();
    for (const auto &item: items_) {
        text_painter_.DrawText(item);
    }
    ui_->screen->setPixmap(text_painter_.GetResultPixmap().scaled(current_image_size_, Qt::KeepAspectRatioByExpanding));
}

void MainWindow::on_database_table_view_data_changed(const QModelIndex &index) {
    for (int i = 0; i < 3; ++i) {
        items_[i].content = table_model_->index(index.row(), i).data().toString();
    }
    ReDrawImage();
}
