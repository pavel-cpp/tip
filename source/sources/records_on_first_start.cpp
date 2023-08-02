#include "../headers/records_on_first_start.h"
#include "ui_records_on_first_start.h"


Records_on_first_start::Records_on_first_start(unsigned* ammount, QDialog *parent) :
        ammount(ammount),
        QDialog(parent),
        ui(new Ui::Records_on_first_start) {
    ui->setupUi(this);
    QFile qssFile("./themes/White.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss = QLatin1String(qssFile.readAll());
    this->setStyleSheet(qss);
    qssFile.close();
    *this->ammount = 500;
}



Records_on_first_start::~Records_on_first_start() {
    delete ui;
}

void Records_on_first_start::on_spinBox_valueChanged(int arg1) {
    *ammount = arg1;
}

void Records_on_first_start::on_pushButton_clicked() {
    close();
}
