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
#include <QGraphicsScene>
#include <QGraphicsTextItem>

// STL
#include <array>

// Services
#include <services/database/models/font_settings_model.h>
#include <services/settings/const_options.h>

QT_BEGIN_NAMESPACE
namespace Ui { class TextPositionSelector; }
QT_END_NAMESPACE

class TextPositionSelector : public QDialog {
Q_OBJECT

public:
    explicit TextPositionSelector(std::array<Models::FontSettings, 3> &font_settings, QDialog *parent = nullptr);

    ~TextPositionSelector() override;

private slots:

    void on_button_box_accepted();

    void on_button_box_rejected();

private:
    Ui::TextPositionSelector *ui;

    QGraphicsScene scene_;
    std::array<QGraphicsTextItem, 3> items_;

    std::array<Models::FontSettings, 3> &font_settings_;
};
