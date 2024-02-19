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

class FontEditor : public QDialog {
Q_OBJECT

public:
    explicit FontEditor(Models::FontSettings &font_settings, QWidget *parent = nullptr);

    ~FontEditor() override;

private slots:

    void on_red_slider_valueChanged(int value);

    void on_green_slider_valueChanged(int value);

    void on_blue_slider_valueChanged(int value);

    void on_font_combo_box_currentFontChanged(const QFont &font);

    void on_bold_check_box_stateChanged(int value);

    void on_size_spin_box_valueChanged(int value);

    void on_save_button_clicked();

private:

    void LoadFontSettings();

    Models::FontSettings font_settings_buffer_;

    Models::FontSettings &font_settings_;

    Ui::FontEditor *ui;
};
