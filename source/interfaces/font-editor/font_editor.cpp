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

#include "font_editor.h"
#include <ui_font_editor.h>

FontEditor::FontEditor(Models::FontSettings &font_settings, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::FontEditor),
        font_settings_(font_settings) {
    ui->setupUi(this);
    font_settings_buffer_ = font_settings_;
    ui->font_combo_box->setCurrentFont(font_settings_buffer_.font.family());
    ui->bold_check_box->setCheckState(
            font_settings_buffer_.font.bold() ?
            Qt::CheckState::Checked :
            Qt::CheckState::Unchecked
    );
    ui->size_spin_box->setValue(font_settings_buffer_.font.pixelSize());
    ui->red_slider->setValue(font_settings_buffer_.color.red());
    ui->green_slider->setValue(font_settings_buffer_.color.green());
    ui->blue_slider->setValue(font_settings_buffer_.color.blue());
    LoadFontSettings();
}

FontEditor::~FontEditor() {
    delete ui;
}

void FontEditor::LoadFontSettings() {
    ui->example_label->setStyleSheet(
            QString(
                    "color: %1;\n"
                    "font-family: %2;\n"
                    "font-size: %3px;\n"
                    "font-weight: %4;"
            )
                    .arg(font_settings_buffer_.color.name(QColor::HexRgb))
                    .arg(font_settings_buffer_.font.family())
                    .arg(font_settings_buffer_.font.pixelSize())
                    .arg(font_settings_buffer_.font.bold() ? "bold" : "normal")
    );
    ui->red_value_label->setText(QString::fromStdString(std::to_string(font_settings_buffer_.color.red())));
    ui->green_value_label->setText(QString::fromStdString(std::to_string(font_settings_buffer_.color.green())));
    ui->blue_value_label->setText(QString::fromStdString(std::to_string(font_settings_buffer_.color.blue())));
}

void FontEditor::on_red_slider_valueChanged(int value) {
    font_settings_buffer_.color.setRed(value);
    LoadFontSettings();
}


void FontEditor::on_green_slider_valueChanged(int value) {
    font_settings_buffer_.color.setGreen(value);
    LoadFontSettings();
}

void FontEditor::on_blue_slider_valueChanged(int value) {
    font_settings_buffer_.color.setBlue(value);
    LoadFontSettings();
}

void FontEditor::on_font_combo_box_currentFontChanged(const QFont &font) {
    font_settings_buffer_.font.setFamily(font.family());
    LoadFontSettings();
}

void FontEditor::on_bold_check_box_stateChanged(int value) {
    font_settings_buffer_.font.setBold(value);
    LoadFontSettings();
}

void FontEditor::on_size_spin_box_valueChanged(int value) {
    font_settings_buffer_.font.setPixelSize(value);
    LoadFontSettings();
}

void FontEditor::on_save_button_clicked() {
    font_settings_ = font_settings_buffer_;
    accept();
}

