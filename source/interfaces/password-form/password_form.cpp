#include "password_form.h"
#include "ui_password_form.h"

#include <QMessageBox>

PasswordForm::PasswordForm(const Models::Passwords& passwords, QWidget *parent) :
        passwords_(passwords),
        QDialog(parent),
        ui(new Ui::PasswordForm) {
    ui->setupUi(this);
}

PasswordForm::~PasswordForm() {
    delete ui;
}

void PasswordForm::on_password_edit_returnPressed() {
    if (passwords_.GetPasswords().contains(ui->password_edit->text())) {
        accept();
        return;
    }
    QMessageBox::warning(this, "Предупреждение", "Не верно введен пароль");
}
