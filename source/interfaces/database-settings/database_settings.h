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

#pragma once

// Qt
#include <QDialog>

// Services
#include <services/database/models/database_options_model.h>

QT_BEGIN_NAMESPACE
namespace Ui { class DatabaseSettings; }
QT_END_NAMESPACE

class DatabaseSettings : public QDialog {
Q_OBJECT

public:
    explicit DatabaseSettings(Models::Database &database_settings_, QWidget *parent = nullptr);

    ~DatabaseSettings() override;

private slots:

    void on_host_edit_textChanged(const QString &text);

    void on_port_edit_textChanged(const QString &text);

    void on_username_edit_textChanged(const QString &text);

    void on_password_edit_textChanged(const QString &text);

    void on_database_edit_textChanged(const QString &text);

    void on_schema_edit_textChanged(const QString &text);

    void on_test_button_clicked();

    void on_save_button_clicked();

private:

    Ui::DatabaseSettings *ui;

    Models::Database &database_settings_;
    Models::Database database_settings_buffer_;

};
