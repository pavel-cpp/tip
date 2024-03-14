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
#include <QColor>
#include <QDialog>

// Services
#include <services/database/models/font_settings_model.h>

namespace Ui {
    class FontEditor;
}

/**
 * @class FontEditor
 * @brief The FontEditor class provides a dialog for managing font settings.
 *
 * This class provides a QDialog with fields for the user to input font settings such as color, font type, boldness, and size.
 * It also provides a save button to store the settings.
 */
class FontEditor : public QDialog {
Q_OBJECT

public:
    /**
     * @brief Construct a new Font Editor object
     *
     * @param font_settings Reference to a FontSettings object where the settings will be stored.
     * @param parent Pointer to the parent QWidget. Default is nullptr.
     */
    explicit FontEditor(Models::FontSettings &font_settings, QWidget *parent = nullptr);

    /**
     * @brief Destroy the Font Editor object
     */
    ~FontEditor() override;

private slots:

    /**
     * @brief Slot for handling changes in the red color slider.
     *
     * @param value The new value of the red color slider.
     */
    void on_red_slider_valueChanged(int value);

    /**
     * @brief Slot for handling changes in the green color slider.
     *
     * @param value The new value of the green color slider.
     */
    void on_green_slider_valueChanged(int value);

    /**
     * @brief Slot for handling changes in the blue color slider.
     *
     * @param value The new value of the blue color slider.
     */
    void on_blue_slider_valueChanged(int value);

    /**
     * @brief Slot for handling changes in the font type combo box.
     *
     * @param font The new font selected in the combo box.
     */
    void on_font_combo_box_currentFontChanged(const QFont &font);

    /**
     * @brief Slot for handling changes in the boldness check box.
     *
     * @param value The new state of the boldness check box.
     */
    void on_bold_check_box_stateChanged(int value);

    /**
     * @brief Slot for handling changes in the font size spin box.
     *
     * @param value The new value of the font size spin box.
     */
    void on_size_spin_box_valueChanged(int value);

    /**
     * @brief Slot for handling the save button click event.
     *
     * This function saves the current settings to the font_settings_ object and closes the dialog.
     */
    void on_save_button_clicked();

private:

    /**
     * @brief Load the current font settings into the UI.
     */
    void LoadFontSettings();

    Models::FontSettings font_settings_buffer_; ///< Buffer for storing the current settings while they are being edited.

    Models::FontSettings &font_settings_; ///< Reference to the FontSettings object where the settings are stored.

    Ui::FontEditor *ui; ///< Pointer to the UI object for this dialog.
};