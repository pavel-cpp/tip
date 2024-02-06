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
