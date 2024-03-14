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

/**
 * @class DatabaseSettings
 * @brief The DatabaseSettings class provides a dialog for managing database settings.
 *
 * This class provides a QDialog with fields for the user to input database settings such as host, port, username, password, database, and schema.
 * It also provides buttons to test the connection and save the settings.
 */
class DatabaseSettings : public QDialog {
Q_OBJECT

public:
    /**
     * @brief Construct a new Database Settings object
     *
     * @param database_settings_ Reference to a Database object where the settings will be stored.
     * @param parent Pointer to the parent QWidget. Default is nullptr.
     */
    explicit DatabaseSettings(Models::Database &database_settings_, QWidget *parent = nullptr);

    /**
     * @brief Destroy the Database Settings object
     */
    ~DatabaseSettings() override;

private slots:

    /**
     * @brief Slot for handling changes in the host field.
     *
     * @param text The new text in the host field.
     */
    void on_host_edit_textChanged(const QString &text);

    /**
     * @brief Slot for handling changes in the port field.
     *
     * @param text The new text in the port field.
     */
    void on_port_edit_textChanged(const QString &text);

    /**
     * @brief Slot for handling changes in the username field.
     *
     * @param text The new text in the username field.
     */
    void on_username_edit_textChanged(const QString &text);

    /**
     * @brief Slot for handling changes in the password field.
     *
     * @param text The new text in the password field.
     */
    void on_password_edit_textChanged(const QString &text);

    /**
     * @brief Slot for handling changes in the database field.
     *
     * @param text The new text in the database field.
     */
    void on_database_edit_textChanged(const QString &text);

    /**
     * @brief Slot for handling changes in the schema field.
     *
     * @param text The new text in the schema field.
     */
    void on_schema_edit_textChanged(const QString &text);

    /**
     * @brief Slot for handling the test button click event.
     */
    void on_test_button_clicked();

    /**
     * @brief Slot for handling the save button click event.
     */
    void on_save_button_clicked();

private:

    Ui::DatabaseSettings *ui; ///< Pointer to the UI object for this dialog.

    Models::Database &database_settings_; ///< Reference to the Database object where the settings are stored.
    Models::Database database_settings_buffer_; ///< Buffer for storing the current settings while they are being edited.

};
