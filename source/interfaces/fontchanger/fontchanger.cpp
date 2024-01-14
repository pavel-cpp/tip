#include "fontchanger.h"
#include <ui_fontchanger.h>

FontChanger::FontChanger(QFont *font, QColor *color, QWidget *parent) :
        oldFont(font),
        oldColor(color),
        QDialog(parent),
        ui(new Ui::FontChanger) {
    ui->setupUi(this);
    init = false;
    ui->fontComboBox->setCurrentFont(*oldFont);
    ui->bold->setCheckState(oldFont->bold() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->spinBox->setValue(oldFont->pixelSize());
    ui->example->setFont(*oldFont);
    ui->red->setValue(oldColor->red());
    ui->green->setValue(oldColor->green());
    ui->blue->setValue(oldColor->blue());
    QVariant var = *oldColor;
    ui->example->setStyleSheet("color: " + var.toString());
    init = true;
    QIcon icon("./icon.png");
    this->setWindowIcon(icon);
}

FontChanger::~FontChanger() {
    delete ui;
}

void FontChanger::changeFont() {
    if (init) {
        font = ui->fontComboBox->currentFont();
        font.setPixelSize(ui->spinBox->value());
        font.setBold(ui->bold->checkState() == Qt::CheckState::Checked ? true : false);
        ui->example->setFont(font);
        color.setRgb(ui->red->value(), ui->green->value(), ui->blue->value());
        QVariant var = color;
        ui->example->setStyleSheet("color: " + var.toString());
    }
}

void FontChanger::on_red_valueChanged(int value) {
    ui->redSpinBox->setValue(value);
    changeFont();
}

void FontChanger::on_redSpinBox_valueChanged(int arg1) {
    ui->red->setValue(arg1);
    changeFont();
}

void FontChanger::on_green_valueChanged(int value) {
    ui->greenSpinBox->setValue(value);
    changeFont();
}

void FontChanger::on_greenSpinBox_valueChanged(int arg1) {
    ui->green->setValue(arg1);
    changeFont();
}

void FontChanger::on_blue_valueChanged(int value) {
    ui->blueSpinBox->setValue(value);
    changeFont();
}

void FontChanger::on_blueSpinBox_valueChanged(int arg1) {
    ui->blue->setValue(arg1);
    changeFont();
}

void FontChanger::on_fontComboBox_currentFontChanged(const QFont &f) {
    changeFont();
}

void FontChanger::on_bold_stateChanged(int arg1) {
    changeFont();
}

void FontChanger::on_spinBox_valueChanged(int arg1) {
    changeFont();
}

void FontChanger::on_save_clicked() {
    *oldFont = font;
    *oldColor = color;
    close();
}
