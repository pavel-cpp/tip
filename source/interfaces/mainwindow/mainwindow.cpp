/*
    "Text Insertion Program (TIP)" is a software
    for client management and generating unique images for each client.
    Copyright (C) 2024  Pavel Remdenok

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include <ui_mainwindow.h>

// Services
#include <services/image-printer/image_printer.h>
#include <services/theme-loader/theme_loader.h>

// Interfaces
#include <interfaces/password-form/password_form.h>
#include <interfaces/records-amount-form/records_amount_form.h>

// Qt
#include <QClipboard>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

// XLSX
#include <OpenXLSX.hpp>

QString operator ""_qs(const char *text, size_t len) {
    return {text};
}

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

    log_.Info("Starting...");

    if (!database_.connect()) {
        QMessageBox::critical(this, "Ошибка!", "Не удалось подключиться к базе данных");
    }
    log_.Info("DatabaseModel initialized");

    table_model_ = std::make_unique<QSqlTableModel>(this, database_.db);
    table_model_->setTable(database_.schema + ".clients");
    table_model_->select();
    table_model_->sort(0, Qt::SortOrder::AscendingOrder);

    log_.Info("DatabaseModel table_model_ initialized");

    connect(
        table_model_.get(),
        SIGNAL(
            dataChanged(
                const QModelIndex &, const QModelIndex &, const QVector<int> &)
        ),
        this,
        SLOT(
            database_table_view_data_changed(
                const QModelIndex&)
        )
    );

    ui->database_table_view->setModel(table_model_.get());
    ui->database_table_view->setColumnHidden(0, true);
    log_.Info("DatabaseModel table_model_ set to table");

    ui->database_table_view->addActions(ui->menubar->actions());

    text_painter_.SetImage(settings_manager_.GetSettings().image);

    for (int i = 0; i < 3; ++i) {
        items_[i].options = settings_manager_.GetSettings().font_settings[i];
    }

    for (const auto& item : items_) {
        text_painter_.DrawText(item);
    }

    current_image_size_ = text_painter_.GetOriginalImage().size();

    ui->progress_bar->setVisible(false);

    ui->screen->setPixmap(text_painter_.GetResultPixmap());

    log_.Info("Initializing done!");
}

MainWindow::~MainWindow() {
    log_.Info("Closed!");
}

void MainWindow::on_copy_triggered() {
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setImage(text_painter_.GetResultImage(), QClipboard::Clipboard);
    ui->statusbar->showMessage("Картинка успешно скопирована в буфер обмена!");
    log_.Info("Image successfully copied");
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
    log_.Info("Settings saved");
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
        + ".jpeg"
    );
    if (status) {
        ui->statusbar->showMessage(
            "image_"
            + items_[0].content
            + " успешно сохранена!"
        );
    } else {
        ui->statusbar->showMessage("Ошибка сохранения картинки!");
    }
}

void MainWindow::on_print_triggered() {
    log_.Info("Print triggered");
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::NativeFormat);
    QModelIndexList indexes = ui->database_table_view->selectionModel()->selectedRows();
    if (indexes.empty()) {
        QMessageBox::warning(this, "Предупреждение!", "Перед печатью выберете записи!");
        return;
    }
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Rejected) {
        log_.Info("Printer rejected");
        return;
    }
    ImagePrinter image_printer(
        {
            ImagePrinter::FromCentimetersToPixels(7, printer.resolution()),
            ImagePrinter::FromCentimetersToPixels(4, printer.resolution())
        },
        &printer
    );
    for (const auto& index : indexes) {
        table_model_->setData(
            table_model_->index(index.row(), table_model_->fieldIndex("status")),
            true,
            Qt::EditRole
        );
        if (!table_model_->submit()) {
            QMessageBox::critical(
                this,
                "Ошибка!",
                "Ошибка при отправке изменений в базу данных:" + table_model_->lastError().text()
            );
            break;
        }

        SetContents(index);

        text_painter_.Clear();
        for (const auto& item : items_) {
            text_painter_.DrawText(item);
        }

        image_printer.AddPixmap(text_painter_.GetResultPixmap());
    }
    log_.Info("Print started");
}

void MainWindow::on_database_table_view_clicked(const QModelIndex& index) {
    log_.Info("On table clicked");
    SetContents(index);
    ReDrawImage();
}

void MainWindow::on_database_search_textChanged() {
    log_.Info("Searching " + ui->database_search->text().toStdString());
    for (int i = 0; i <= table_model_->rowCount(); i++) {
        for (int j = 0; j <= table_model_->columnCount(); j++) {
            if (table_model_->index(i, j).data().toString().contains(ui->database_search->text())) {
                log_.Info("Found: " + table_model_->index(i, j).data().toString().toStdString());
                if (ui->database_table_view->isRowHidden(i)) ui->database_table_view->showRow(i);
                break;
            } else {
                if (!ui->database_table_view->isRowHidden(i)) ui->database_table_view->hideRow(i);
            }
        }
    }
}

void MainWindow::on_show_database_triggered() {
    log_.Info("DatabaseModel visible: true");
    ui->database_dock->setVisible(true);
}

void MainWindow::on_hide_database_triggered() {
    log_.Info("DatabaseModel visible: false");
    ui->database_dock->setVisible(false);
}

void MainWindow::on_show_image_triggered() {
    log_.Info("Image visible: true");
    ui->database_dock->setVisible(true);
}

void MainWindow::on_hide_image_triggered() {
    log_.Info("Image visible: false");
    ui->database_dock->setVisible(false);
}

void MainWindow::on_image_scale_up_triggered() {
    log_.Info("Image scaled up");
    current_image_size_.setWidth(current_image_size_.width() + 50);
    current_image_size_.setHeight(current_image_size_.height() + 50);
    ReDrawImage();
}

void MainWindow::on_image_scale_down_triggered() {
    log_.Info("Image scaled down");
    current_image_size_.setWidth(current_image_size_.width() - 50);
    current_image_size_.setHeight(current_image_size_.height() - 50);
    ReDrawImage();
}

void MainWindow::on_save_some_images_triggered() {
    log_.Info("Save some images triggered!");
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
    for (const auto& selected_row : selected_rows) {
        ui->progress_bar->setValue(progress_index);
        QCoreApplication::processEvents();

        SetContents(selected_row);

        text_painter_.Clear();
        for (const auto& item : items_) {
            text_painter_.DrawText(item);
        }

        if (text_painter_.GetResultImage().save(
            settings_manager_.GetSettings().output_folder
            + "/image_"
            + items_[0].content
            + ".jpeg"
        )) {
            ui->statusbar->showMessage(
                "image_"
                + items_[0].content
                + " успешно сохранена!"
            );
            ++progress_index;
        } else {
            ui->statusbar->showMessage(
                "image_"
                + items_[0].content
                + " не сохранена!"
            );
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
    for (const auto& item : items_) {
        text_painter_.DrawText(item);
    }
    ui->screen->setPixmap(text_painter_.GetResultPixmap().scaled(current_image_size_, Qt::KeepAspectRatioByExpanding));
}

void MainWindow::on_export_database_triggered() {
    QFileInfo file_info = QFileDialog::getSaveFileName(
        this,
        tr("Экспортировать"),
        "",
        "Excel(*.xlsx);"
    );
    if(file_info.absoluteFilePath().isEmpty()) {
        return;
    }
    try {
        OpenXLSX::XLDocument document;
        document.create(file_info.absoluteFilePath().toStdString());
        document.workbook().addWorksheet("Report");
        document.workbook().deleteSheet("Sheet1");
        auto worksheet = document.workbook().worksheet("Report");

        size_t rows = table_model_->rowCount();
        size_t cols = table_model_->columnCount();
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                worksheet.cell(row + 1, col + 1).value() = table_model_->index(row, col).data().toString().toStdString();
            }
        }

        document.save();
        ui->statusbar->showMessage("Таблица успешно экспортирована");
    } catch (const std::exception& e) {
        // Обработать исключение (например, показать сообщение об ошибке)
        QMessageBox::warning(this, "Ошибка!", tr("Ошибка: ")  + e.what());
    }
}

void MainWindow::database_table_view_data_changed(const QModelIndex& index) {
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
            QSqlQuery query(database_.db);
            ui->progress_bar->setMaximum(amount - 1);
            ui->progress_bar->setVisible(true);
            for (int i = 0; i < amount; ++i) {
                query.exec(
                    QString("INSERT INTO %1.clients (name, phone_number, status) VALUES ('', '', false);").arg(
                        database_.schema
                    )
                );
                ui->progress_bar->setValue(i);
                QCoreApplication::processEvents();
            }
            table_model_->select();
            ui->progress_bar->setVisible(false);
        }
    }
}

void MainWindow::SetContents(const QModelIndex& index) {
    for (int i = 0; i < 3; ++i) {
        items_[i].content = table_model_->index(index.row(), i).data().toString();
    }
}

void MainWindow::on_clear_database_triggered() {
    if (PasswordForm(settings_manager_.GetSettings().passwords, this).exec() != QDialog::Accepted) {
        return;
    }
    QSqlQuery query(database_.db);
    QString drop_table("DROP TABLE IF EXISTS %1.%2;");
    QString create_table(
        "CREATE TABLE IF NOT EXISTS %1.%2\n"
        "(\n"
        "    ID           SERIAL\n"
        "        PRIMARY KEY,\n"
        "    name         VARCHAR(255),\n"
        "    phone_number VARCHAR(255),\n"
        "    status       BOOLEAN DEFAULT false\n"
        ");"
    );
    query.exec(drop_table.arg(database_.schema).arg("clients_backup"));
    query.exec(create_table.arg(database_.schema).arg("clients_backup"));

    query.exec(
        "INSERT INTO %1.clients_backup (id, name, phone_number, status) "
        "SELECT * FROM %1.clients"_qs.arg(database_.schema)
    );

    query.exec(drop_table.arg(database_.schema).arg("clients"));
    query.exec(create_table.arg(database_.schema).arg("clients"));
    table_model_->select();
}
