#include "options.h"
#include <ui_options.h>

#include <Qdir>
#include <QColor>

Options::Options(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Options),
        settings_manager_("default_settings") {
    ui->setupUi(this);
    auto settings = settings_manager_.GetSettings();
    ui->path_to_edit->setText(settings.output_folder);
    QDir dir(settings.consts.themes_dir);
    auto themes = dir.entryList();
    for(const auto& theme: themes){
        ui->theme_combo_box->addItem(theme);
    }
    ui->example_1->setFont(settings.font_settings[0].font);
    ui->example_1->setStyleSheet("color: " + settings.font_settings[0].color.name(QColor::HexRgb) + ";");
    ui->example_2->setFont(settings.font_settings[1].font);
    ui->example_2->setStyleSheet("color: " + settings.font_settings[1].color.name(QColor::HexRgb) + ";");
    ui->example_3->setFont(settings.font_settings[2].font);
    ui->example_3->setStyleSheet("color: " + settings.font_settings[2].color.name(QColor::HexRgb) + ";");
}

Options::~Options() {
    delete ui;
}

void Options::on_path_to_edit_textEdited() {

}

void Options::on_path_to_button_clicked() {

}

void Options::on_theme_combo_box_currentIndexChanged(int) {

}

void Options::on_change_button_ex_1_clicked() {

}

void Options::on_change_button_ex_2_clicked() {

}

void Options::on_change_button_ex_3_clicked() {

}

void Options::on_change_text_position_button_clicked() {

}

void Options::on_database_edit_button_clicked() {

}

void Options::on_save_button_clicked() {

}

