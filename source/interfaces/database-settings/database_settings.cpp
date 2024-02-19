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

#include "database_settings.h"
#include "ui_database_settings.h"

// Services
#include <services/database/database.h>

DatabaseSettings::DatabaseSettings(Models::Database &database_settings, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::DatabaseSettings),
        database_settings_(database_settings),
        database_settings_buffer_(database_settings) {
    ui->setupUi(this);
    ui->host_edit->setText(database_settings_.host);
    ui->port_edit->setText(QString::fromStdString(std::to_string(database_settings_.port)));
    ui->username_edit->setText(database_settings_.username);
    ui->password_edit->setText(database_settings_.password);
    ui->database_edit->setText(database_settings_.name);
    ui->schema_edit->setText(database_settings_.schema);
}

DatabaseSettings::~DatabaseSettings() {
    delete ui;
}

void DatabaseSettings::on_host_edit_textChanged(const QString &text) {
    database_settings_buffer_.host = text;
}

void DatabaseSettings::on_port_edit_textChanged(const QString &text) {
    database_settings_buffer_.port = text.toUInt();
}

void DatabaseSettings::on_username_edit_textChanged(const QString &text) {
    database_settings_buffer_.username = text;
}

void DatabaseSettings::on_password_edit_textChanged(const QString &text) {
    database_settings_buffer_.password = text;
}

void DatabaseSettings::on_database_edit_textChanged(const QString &text) {
    database_settings_buffer_.name = text;
}

void DatabaseSettings::on_schema_edit_textChanged(const QString &text) {
    database_settings_buffer_.schema = text;
}

void DatabaseSettings::on_test_button_clicked() {
    Database test_database(database_settings_buffer_, "test");
    if (test_database.connect()) {
        ui->status_label->setText("Статус: Ok");
        test_database.disconnect();
    } else {
        ui->status_label->setText("Статус: Ошибка подключения");
    }
}

void DatabaseSettings::on_save_button_clicked() {
    database_settings_ = database_settings_buffer_;
    accept();
}

