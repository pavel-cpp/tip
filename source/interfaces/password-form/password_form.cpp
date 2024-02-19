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

#include "password_form.h"
#include "ui_password_form.h"

// Qt
#include <QMessageBox>

PasswordForm::PasswordForm(const Models::Passwords &passwords, QWidget *parent) :
        passwords_(passwords),
        QDialog(parent),
        ui(new Ui::PasswordForm) {
    ui->setupUi(this);
}

PasswordForm::~PasswordForm() {
    delete ui;
}

void PasswordForm::on_password_edit_returnPressed() {
    if (passwords_.GetPasswords().size() == 1 && passwords_.GetPasswords().last() == ui->password_edit->text()) {
        accept();
        return;
    }
    if (passwords_.GetPasswords().contains(ui->password_edit->text()) && ui->password_edit->text() != "root") {
        accept();
        return;
    }
    QMessageBox::warning(this, "Предупреждение", "Не верно введен пароль");
}
