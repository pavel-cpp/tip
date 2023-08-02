#include "../headers/records_ammount.h"
#include "ui_records_ammount.h"

RecordsAmmount::RecordsAmmount(unsigned *amount, QWidget *parent) :
        amount(amount), QDialog(parent), ui(new Ui::RecordsAmmount) {
    ui->setupUi(this);
    QIcon icon("./icon.png");
    this->setWindowIcon(icon);
    QFile qssFile("./themes/White.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss = QLatin1String(qssFile.readAll());
    this->setStyleSheet(qss);
    qssFile.close();
}

RecordsAmmount::~RecordsAmmount() {
    reject();
    delete ui;
}

void RecordsAmmount::on_ok_clicked() {
    accept();
    close();
}

void RecordsAmmount::on_horizontalSlider_valueChanged(int value) {
    if (ui->spinBox->value() != value) {
    ui->spinBox->setValue(value);
    }
}

void RecordsAmmount::on_spinBox_valueChanged(int value) {
    *amount = value;
    if(ui->spinBox->value() != value) {
        ui->spinBox->setValue(value);
    }
}
