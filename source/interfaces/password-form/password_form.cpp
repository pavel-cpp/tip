//
// Created by green on 30-Jan-24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_password_form.h" resolved

#include "password_form.h"
#include "ui_password_form.h"


password_form::password_form(QWidget *parent) :
        QDialog(parent), ui(new Ui::password_form) {
    ui->setupUi(this);
}

password_form::~password_form() {
    delete ui;
}
