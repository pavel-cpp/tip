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

/**
 * @class TextPositionSelector
 * @brief The TextPositionSelector class provides a dialog for selecting the position of text.
 *
 * This class provides a QDialog with a graphical interface for the user to select the position of text.
 * It also provides buttons to accept or reject the changes.
 */
class TextPositionSelector : public QDialog {
Q_OBJECT

public:
    /**
     * @brief Construct a new Text Position Selector object
     *
     * @param font_settings Reference to an array of FontSettings objects where the settings will be stored.
     * @param parent Pointer to the parent QWidget. Default is nullptr.
     */
    explicit TextPositionSelector(std::array<Models::FontSettings, 3> &font_settings, QDialog *parent = nullptr);

    /**
     * @brief Destroy the Text Position Selector object
     */
    ~TextPositionSelector() override;

private slots:

    /**
     * @brief Slot for handling the accepted event of the button box.
     *
     * This function saves the current settings and closes the dialog.
     */
    void on_button_box_accepted();

    /**
     * @brief Slot for handling the rejected event of the button box.
     *
     * This function discards the current settings and closes the dialog.
     */
    void on_button_box_rejected();

private:

    Ui::TextPositionSelector *ui; ///< Pointer to the UI object for this dialog.

    QGraphicsScene scene_; ///< QGraphicsScene object for displaying the graphical interface.

    std::array<QGraphicsTextItem, 3> items_; ///< Array of QGraphicsTextItem objects for displaying the text items.

    std::array<Models::FontSettings, 3> &font_settings_; ///< Reference to the array of FontSettings objects where the settings are stored.
};