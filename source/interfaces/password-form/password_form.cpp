#include "password_form.h"
#include "ui_password_form.h"

#include <QMessageBox>
#include <QDebug>

PasswordForm::PasswordForm(const Models::Passwords &passwords, QWidget *parent) :
        passwords_(passwords),
        QDialog(parent),
        ui(new Ui::PasswordForm) {
    qDebug() << passwords_.GetPasswords() << endl;
    ui->setupUi(this);
}

PasswordForm::~PasswordForm() {
    delete ui;
}

void PasswordForm::on_password_edit_returnPressed() {
    qDebug() << passwords_.GetPasswords() << passwords_.GetPasswords().size();
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
