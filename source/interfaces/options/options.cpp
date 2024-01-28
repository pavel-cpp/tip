#include "options.h"
#include <ui_options.h>

#include <Qdir>
#include <QColor>
#include <QFileDialog>

#include <services/theme-loader/theme_loader.h>
#include <interfaces/text-position-selector/text_position_selector.h>
#include <interfaces/font-editor/font_editor.h>
#include <interfaces/database-settings/database_settings.h>

Options::Options(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Options),
        settings_manager_("default_settings") {
    ui->setupUi(this);
    settings_buffer_ = settings_manager_.GetSettings();
    ui->path_to_edit->setText(settings_buffer_.output_folder);
    QDir dir(settings_buffer_.consts.themes_dir);
    ui->theme_combo_box->addItem(settings_buffer_.theme);
    for (const auto &theme: dir.entryList()) {
        if (theme == "." || theme == ".." || !theme.contains(".qss") || theme == settings_buffer_.theme + ".qss") {
            continue;
        }
        ui->theme_combo_box->addItem(theme.split(".qss").front());
    }
    ui->example_1->setFont(settings_buffer_.font_settings[0].font);
    ui->example_1->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(settings_buffer_.font_settings[0].color.name(QColor::HexRgb)).arg(settings_buffer_.font_settings[0].font.pixelSize()));
    ui->example_2->setFont(settings_buffer_.font_settings[1].font);
    ui->example_2->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(settings_buffer_.font_settings[1].color.name(QColor::HexRgb)).arg(settings_buffer_.font_settings[1].font.pixelSize()));
    ui->example_3->setFont(settings_buffer_.font_settings[2].font);
    ui->example_3->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(settings_buffer_.font_settings[2].color.name(QColor::HexRgb)).arg(settings_buffer_.font_settings[2].font.pixelSize()));
}

Options::~Options() {
    delete ui;
}

void Options::on_path_to_button_clicked() {
    QString folder = QFileDialog::getExistingDirectory(
            this,
            tr("Выберите папку для сохранения"),
            QDir::homePath()
    );
    if(!folder.isEmpty()){
        ui->path_to_edit->setText(folder);
        settings_buffer_.output_folder = folder;
    }
}

void Options::on_theme_combo_box_currentIndexChanged(int) {
    settings_buffer_.theme = ui->theme_combo_box->currentText();
    setStyleSheet(Theme::Load(settings_buffer_.theme));
}

void Options::on_change_button_ex_1_clicked() {
    FontEditor(settings_buffer_.font_settings[0], this).exec();
    ui->example_1->setFont(settings_buffer_.font_settings[0].font);
    ui->example_1->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(settings_buffer_.font_settings[0].color.name(QColor::HexRgb)).arg(settings_buffer_.font_settings[0].font.pixelSize()));
}

void Options::on_change_button_ex_2_clicked() {
    FontEditor(settings_buffer_.font_settings[1], this).exec();
    ui->example_2->setFont(settings_buffer_.font_settings[1].font);
    ui->example_2->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(settings_buffer_.font_settings[1].color.name(QColor::HexRgb)).arg(settings_buffer_.font_settings[1].font.pixelSize()));
}

void Options::on_change_button_ex_3_clicked() {
    FontEditor(settings_buffer_.font_settings[2], this).exec();
    ui->example_3->setFont(settings_buffer_.font_settings[2].font);
    ui->example_3->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(settings_buffer_.font_settings[2].color.name(QColor::HexRgb)).arg(settings_buffer_.font_settings[2].font.pixelSize()));
}

void Options::on_change_text_position_button_clicked() {
    TextPositionSelector(settings_buffer_.font_settings, this).exec();
}

void Options::on_database_edit_button_clicked() {
    DatabaseSettings(settings_buffer_.database, this).exec();
}

void Options::on_save_button_clicked() {
    settings_manager_.SetSettings(settings_buffer_);
    settings_manager_.Save();
    close();
}

void Options::on_path_to_edit_textChanged(const QString& text) {
    settings_buffer_.output_folder = text;
}

void Options::on_image_url_edit_textChanged(const QString &text) {

}

void Options::on_image_format_edit_textChanged(const QString &text) {

}

