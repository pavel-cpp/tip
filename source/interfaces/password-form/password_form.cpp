#include "password_form.h"
#include "ui_password_form.h"

#include <QMessageBox>

PasswordForm::PasswordForm(QWidget *parent) :
        QDialog(parent), ui(new Ui::PasswordForm) {
    ui->setupUi(this);
}

PasswordForm::~PasswordForm() {
    delete ui;
}

void PasswordForm::on_password_edit_returnPressed() {
    if (ui->password_edit->text() == "test") {
        accept();
        return;
    }
    QMessageBox::warning(this, "Предупреждение", "Не верно введен пароль");
}
