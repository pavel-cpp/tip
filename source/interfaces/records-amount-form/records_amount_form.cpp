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

#include "records_amount_form.h"
#include "ui_records_amount_form.h"

RecordsAmountForm::RecordsAmountForm(int &amount, QWidget *parent) :
        amount_(amount),
        QDialog(parent),
        ui(new Ui::RecordsAmountForm) {
    ui->setupUi(this);
}

RecordsAmountForm::~RecordsAmountForm() {
    delete ui;
}

void RecordsAmountForm::on_add_button_clicked() {
    amount_ = ui->records_amount_spin_box->value();
    accept();
}
