#include "database_settings.h"
#include "ui_database_settings.h"

DatabaseSettings::DatabaseSettings(QWidget *parent) :
        QDialog(parent), ui(new Ui::database_settings) {
    ui->setupUi(this);
}

DatabaseSettings::~DatabaseSettings() {
    delete ui;
}
