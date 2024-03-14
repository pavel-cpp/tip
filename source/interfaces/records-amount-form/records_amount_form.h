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

QT_BEGIN_NAMESPACE
namespace Ui { class RecordsAmountForm; }
QT_END_NAMESPACE

/**
 * @class RecordsAmountForm
 * @brief The RecordsAmountForm class provides a dialog for specifying the amount of records.
 *
 * This class provides a QDialog with a field for the user to input the amount of records.
 * It also provides a button to submit the amount.
 */
class RecordsAmountForm : public QDialog {
Q_OBJECT

public:
    /**
     * @brief Construct a new Records Amount Form object
     *
     * @param amount Reference to an integer where the amount will be stored.
     * @param parent Pointer to the parent QWidget. Default is nullptr.
     */
    explicit RecordsAmountForm(int &amount, QWidget *parent = nullptr);

    /**
     * @brief Destroy the Records Amount Form object
     */
    ~RecordsAmountForm() override;

private slots:

    /**
     * @brief Slot for handling the add_button click event.
     *
     * This function submits the entered amount.
     */
    void on_add_button_clicked();

private:

    int &amount_; ///< Reference to the integer where the amount is stored.

    Ui::RecordsAmountForm *ui; ///< Pointer to the UI object for this dialog.
};