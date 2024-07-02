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
#include <services/settings/settings_manager.h>

namespace Ui {
    class Options;
}

/**
 * @class Options
 * @brief The Options class provides a dialog for managing application settings.
 *
 * This class provides a QDialog with fields for the user to input settings such as path, theme, text position, database, image URL, and image format.
 * It also provides buttons to save the settings and access advanced settings.
 */
class Options : public QDialog {
Q_OBJECT

public:
    /**
     * @brief Construct a new Options object
     *
     * @param parent Pointer to the parent QWidget. Default is nullptr.
     */
    explicit Options(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Options object
     */
    ~Options() override;

private slots:

    /**
     * @brief Slot for handling the path_to_button click event.
     */
    void on_path_to_button_clicked();

    /**
     * @brief Slot for handling changes in the path_to_edit field.
     *
     * @param text The new text in the path_to_edit field.
     */
    void on_path_to_edit_textChanged(const QString &text);

    /**
     * @brief Slot for handling changes in the theme_combo_box.
     *
     * @param index The new index of the theme_combo_box.
     */
    void on_theme_combo_box_currentIndexChanged(int);

    /**
     * @brief Slot for handling the change_button_ex_1 click event.
     */
    void on_change_button_ex_1_clicked();

    /**
     * @brief Slot for handling the change_button_ex_2 click event.
     */
    void on_change_button_ex_2_clicked();

    /**
     * @brief Slot for handling the change_button_ex_3 click event.
     */
    void on_change_button_ex_3_clicked();

    /**
     * @brief Slot for handling the change_text_position_button click event.
     */
    void on_change_text_position_button_clicked();

    /**
     * @brief Slot for handling the database_edit_button click event.
     */
    void on_database_edit_button_clicked();

    /**
     * @brief Slot for handling the save_button click event.
     *
     * This function saves the current settings and closes the dialog.
     */
    void on_save_button_clicked();

    /**
     * @brief Slot for handling the upload_button click event.
     */
    void on_upload_button_clicked();

    /**
     * @brief Slot for handling the advanced_settings_button click event.
     */
    void on_advanced_settings_button_clicked();

private:

    /**
     * @brief Set the visibility of the advanced settings.
     *
     * @param state The new visibility state of the advanced settings.
     */
    void SetAdvancedSettingsVisible(bool state);

    SettingsManager settings_manager_; ///< SettingsManager object for managing application settings.

    int save_type_ = SettingsManager::SaveType::SAVE_NONE; ///< The current save type.

    SettingsManager::Settings settings_buffer_; ///< Buffer for storing the current settings while they are being edited.

    Ui::Options *ui; ///< Pointer to the UI object for this dialog.
};