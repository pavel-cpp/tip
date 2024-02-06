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
    close();
}

