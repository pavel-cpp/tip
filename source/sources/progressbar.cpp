#include "../headers/progressbar.h"
#include "ui_ProgressBar.h"


ProgressBar::ProgressBar(QWidget *parent) :
        QWidget(parent), ui(new Ui::ProgressBar) {
    ui->setupUi(this);

}

ProgressBar::~ProgressBar() {
    delete ui;
}

void ProgressBar::setValue(unsigned int val) {
    ui->progressBar->setValue(val);
}

void ProgressBar::setMax(unsigned int max) {
    ui->progressBar->setMaximum(max);
}
