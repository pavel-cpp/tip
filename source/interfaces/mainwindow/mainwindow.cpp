#include "mainwindow.h"
#include <ui_mainwindow.h>

#include <services/theme-loader/theme_loader.h>
#include <services/image-downloader/image_downloader.h>
#include <services/image-printer/image_printer.h>

#include <interfaces/password-form/password_form.h>
#include <interfaces/records-amount-form/records_amount_form.h>

#include <QDebug>
#include <QMessageBox>
#include <QPrintPreviewDialog>

const QSizeF dimensionFactor(1.686 * 1.15, 1.481 * 1.15);

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()),
          settings_manager_("mainwindow"),
          database_(settings_manager_.GetSettings().database) {
    ui->setupUi(this);

    this->setStyleSheet(Theme::Load(settings_manager_.GetSettings().theme));

    ui->screen->addAction(ui->copy);
    ui->screen->addAction(ui->save_image);
    ui->screen->addAction(ui->image_scale_up);
    ui->screen->addAction(ui->image_scale_down);

    log_.info("Starting...");

    if (!database_.connect()) {
        QMessageBox::critical(this, "Ошибка!", "Не удалось подключиться к базе данных");
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

    ui->database_table_view->setModel(table_model_.get());
    ui->database_table_view->setColumnHidden(0, true);
    log_.info("DatabaseModel table_model_ set to table");

    ui->database_table_view->addActions(ui->menubar->actions());

    if (!ImageDownloader::FetchImage(
            settings_manager_.GetSettings().consts.source_image_path + "." +
            settings_manager_.GetSettings().image.format,
            settings_manager_.GetSettings().image.url
    )) {
        QMessageBox::warning(this, "Предупреждение!", "Не удалось загрузить изображение!\nНе верно указана ссылка");
    }

    QImage image;

    if (!image.load(settings_manager_.GetSettings().consts.source_image_path + "." +
                    settings_manager_.GetSettings().image.format)) {
        QMessageBox::warning(this, "Предупреждение!",
                             "Не удалось открыть изображение!\nНе верно указан формат изображения или ссылка");
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

    ui->progress_bar->setVisible(false);

    ui->screen->setPixmap(text_painter_.GetResultPixmap());

    log_.info("Initializing done!");
}

MainWindow::~MainWindow() {
    log_.info("Closed!");
}

void MainWindow::on_copy_triggered() {
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setImage(text_painter_.GetResultImage(), QClipboard::Clipboard);
    ui->statusbar->showMessage("Картинка успешно скопирована в буфер обмена!");
    log_.info("Image successfully copied");
}

void MainWindow::on_settings_triggered() {
    Options(this).exec();
    settings_manager_.ReloadSettings();
    for (int i = 0; i < 3; ++i) {
        items_[i].options = settings_manager_.GetSettings().font_settings[i];
    }
    ReDrawImage();
    this->setStyleSheet(Theme::Load(settings_manager_.GetSettings().theme));
    ui->statusbar->showMessage("Настройки сохранены!");
    log_.info("Settings saved");
}

void MainWindow::on_save_image_triggered() {
    if (settings_manager_.GetSettings().output_folder == "default") {
        ui->statusbar->showMessage("Изображение не сохранено! Добавьте путь к папке с результатом!");
        return;
    }
    bool status = text_painter_.GetResultImage().save(
            settings_manager_.GetSettings().output_folder
            + "/image_"
            + items_[0].content
            + "."
            + settings_manager_.GetSettings().image.format
    );
    if (status) {
        ui->statusbar->showMessage("image_"
                                   + items_[0].content
                                   + " успешно сохранена!");
    } else {
        ui->statusbar->showMessage("Ошибка сохранения картинки!");
        qDebug() << settings_manager_.GetSettings().image.url << endl
                 << settings_manager_.GetSettings().image.format << endl;
    }
}

void MainWindow::on_print_triggered() {
    log_.info("Print triggered");
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::NativeFormat);
    QModelIndexList indexes = ui->database_table_view->selectionModel()->selectedRows();
    if (indexes.empty()) {
        QMessageBox::warning(this, "Предупреждение!", "Перед печатью выберете записи!");
        return;
    }
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Rejected) {
        log_.info("Printer rejected");
        return;
    }
    ImagePrinter image_printer({ImagePrinter::FromCentimetersToPixels(7), ImagePrinter::FromCentimetersToPixels(4)},
                               &printer);
    for (const auto &index: indexes) {
        SetContents(index);

        text_painter_.Clear();
        for (const auto &item: items_) {
            text_painter_.DrawText(item);
        }

        image_printer.AddPixmap(text_painter_.GetResultPixmap());
    }
    log_.info("Print started");
}

void MainWindow::on_database_table_view_clicked(const QModelIndex &index) {
    log_.info("On table clicked");
    SetContents(index);
    ReDrawImage();
}

void MainWindow::on_database_search_textChanged() {
    log_.info("Searching " + ui->database_search->text().toStdString());
    for (int i = 0; i <= table_model_->rowCount(); i++) {
        for (int j = 0; j <= table_model_->columnCount(); j++) {
            if (table_model_->index(i, j).data().toString().contains(ui->database_search->text())) {
                log_.info("Found: " + table_model_->index(i, j).data().toString().toStdString());
                if (ui->database_table_view->isRowHidden(i)) ui->database_table_view->showRow(i);
                break;
            } else {
                if (!ui->database_table_view->isRowHidden(i)) ui->database_table_view->hideRow(i);
            }
        }
    }
}

void MainWindow::on_show_database_triggered() {
    log_.info("DatabaseModel visible: true");
    ui->database_dock->setVisible(true);
}

void MainWindow::on_hide_database_triggered() {
    log_.info("DatabaseModel visible: false");
    ui->database_dock->setVisible(false);
}

void MainWindow::on_show_image_triggered() {
    log_.info("Image visible: true");
    ui->database_dock->setVisible(true);
}

void MainWindow::on_hide_image_triggered() {
    log_.info("Image visible: false");
    ui->database_dock->setVisible(false);
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

void MainWindow::on_save_some_images_triggered() {
    log_.info("Save some images triggered!");
    QModelIndexList selected_rows = ui->database_table_view->selectionModel()->selectedRows();
    if (selected_rows.empty()) {
        ui->statusbar->showMessage("Вы не выделили строки!");
        return;
    }

    if (settings_manager_.GetSettings().output_folder == "default") {
        ui->statusbar->showMessage("Изображения не сохранены! Добавьте путь к папке с результатом!");
        return;
    }

    ui->progress_bar->setMaximum(selected_rows.size());
    ui->progress_bar->setVisible(true);

    int progress_index = 0;
    for (const auto &selected_row: selected_rows) {
        ui->progress_bar->setValue(progress_index);
        QCoreApplication::processEvents();

        SetContents(selected_row);

        text_painter_.Clear();
        for (const auto &item: items_) {
            text_painter_.DrawText(item);
        }

        if (text_painter_.GetResultImage().save(
                settings_manager_.GetSettings().output_folder
                + "/image_"
                + items_[0].content
                + "."
                + settings_manager_.GetSettings().image.format
        )) {
            ui->statusbar->showMessage("image_"
                                       + items_[0].content
                                       + " успешно сохранена!");
            ++progress_index;
        } else {
            ui->statusbar->showMessage("image_"
                                       + items_[0].content
                                       + " не сохранена!");
        }
    }

    if (progress_index != selected_rows.size()) {
        ui->statusbar->showMessage("Не все изображения были сохранены!");
        return;
    }

    ui->statusbar->showMessage("Все изображения были успешно сохранены!");

    ui->progress_bar->setVisible(false);
}

void MainWindow::ReDrawImage() {
    text_painter_.Clear();
    for (const auto &item: items_) {
        text_painter_.DrawText(item);
    }
    ui->screen->setPixmap(text_painter_.GetResultPixmap().scaled(current_image_size_, Qt::KeepAspectRatioByExpanding));
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
    if (PasswordForm(settings_manager_.GetSettings().passwords, this).exec() == QDialog::Accepted) {
        table_model_->insertRows(table_model_->rowCount(), 1);
        table_model_->submit();
    }
}

void MainWindow::on_insert_same_records_triggered() {
    if (PasswordForm(settings_manager_.GetSettings().passwords, this).exec() == QDialog::Accepted) {
        int amount;
        if (RecordsAmountForm(amount, this).exec() == QDialog::Accepted) {
            qDebug() << amount << endl;
            QSqlQuery query(database_.db);
            for (int i = 0; i < amount; ++i) {
                query.exec(QString("INSERT INTO %1.clients (name, phone_number, status) VALUES ('', '', false);").arg(
                        database_.schema));
            }
            table_model_->select();
        }
    }
}

void MainWindow::SetContents(const QModelIndex &index) {
    for (int i = 0; i < 3; ++i) {
        items_[i].content = table_model_->index(index.row(), i).data().toString();
    }
}
