#include "options.h"
#include <ui_options.h>

#include <Qdir>
#include <QColor>
#include <QFileDialog>

#include <QMessageBox>

#include <services/theme-loader/theme_loader.h>
#include <interfaces/text-position-selector/text_position_selector.h>
#include <interfaces/font-editor/font_editor.h>
#include <interfaces/database-settings/database_settings.h>
#include <interfaces/password-form/password_form.h>

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
    ui->example_1->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(
            settings_buffer_.font_settings[0].color.name(QColor::HexRgb)).arg(
            settings_buffer_.font_settings[0].font.pixelSize()));
    ui->example_2->setFont(settings_buffer_.font_settings[1].font);
    ui->example_2->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(
            settings_buffer_.font_settings[1].color.name(QColor::HexRgb)).arg(
            settings_buffer_.font_settings[1].font.pixelSize()));
    ui->example_3->setFont(settings_buffer_.font_settings[2].font);
    ui->example_3->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(
            settings_buffer_.font_settings[2].color.name(QColor::HexRgb)).arg(
            settings_buffer_.font_settings[2].font.pixelSize()));
    ui->image_url_edit->setText(settings_buffer_.image.url.toString());
    ui->image_format_edit->setText(settings_buffer_.image.format);

    SetAdvancedSettingsVisible(false);
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
    if (!folder.isEmpty()) {
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
    ui->example_1->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(
            settings_buffer_.font_settings[0].color.name(QColor::HexRgb)).arg(
            settings_buffer_.font_settings[0].font.pixelSize()));
}

void Options::on_change_button_ex_2_clicked() {
    FontEditor(settings_buffer_.font_settings[1], this).exec();
    ui->example_2->setFont(settings_buffer_.font_settings[1].font);
    ui->example_2->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(
            settings_buffer_.font_settings[1].color.name(QColor::HexRgb)).arg(
            settings_buffer_.font_settings[1].font.pixelSize()));
}

void Options::on_change_button_ex_3_clicked() {
    FontEditor(settings_buffer_.font_settings[2], this).exec();
    ui->example_3->setFont(settings_buffer_.font_settings[2].font);
    ui->example_3->setStyleSheet(QString("color: %1;\nfont-size: %2px;").arg(
            settings_buffer_.font_settings[2].color.name(QColor::HexRgb)).arg(
            settings_buffer_.font_settings[2].font.pixelSize()));
}

void Options::on_change_text_position_button_clicked() {
    TextPositionSelector(settings_buffer_.font_settings, this).exec();
}

void Options::on_database_edit_button_clicked() {
    DatabaseSettings(settings_buffer_.database, this).exec();
}

void Options::on_save_button_clicked() {
    if (settings_manager_.GetSettings().image.url != settings_buffer_.image.url ||
        settings_manager_.GetSettings().database.host != settings_buffer_.database.host ||
        settings_manager_.GetSettings().database.port != settings_buffer_.database.port ||
        settings_manager_.GetSettings().database.schema != settings_buffer_.database.schema) {
        QMessageBox::information(this, "Подсказка", "После сохранения настроек перезапустите программу!");
    }
    settings_manager_.SetSettings(settings_buffer_);
    settings_manager_.Save();
    close();
}

void Options::on_path_to_edit_textChanged(const QString &text) {
    settings_buffer_.output_folder = text;
}

void Options::on_image_url_edit_textChanged(const QString &text) {
    settings_buffer_.image.url = text;
}

void Options::on_image_format_edit_textChanged(const QString &text) {
    settings_buffer_.image.format = text;
}

void Options::SetAdvancedSettingsVisible(bool state) {
    ui->formatting_label->setVisible(state);
    ui->formatting_line->setVisible(state);
    ui->example_1->setVisible(state);
    ui->example_2->setVisible(state);
    ui->example_3->setVisible(state);
    ui->change_button_ex_1->setVisible(state);
    ui->change_button_ex_2->setVisible(state);
    ui->change_button_ex_3->setVisible(state);

    ui->text_position_label->setVisible(state);
    ui->text_position_line->setVisible(state);
    ui->change_text_position_label->setVisible(state);
    ui->change_text_position_button->setVisible(state);

    ui->database_label->setVisible(state);
    ui->database_line->setVisible(state);
    ui->database_name->setVisible(state);
    ui->database_edit_button->setVisible(state);

    ui->image_line->setVisible(state);
    ui->image_label->setVisible(state);
    ui->image_format_label->setVisible(state);
    ui->image_format_edit->setVisible(state);
    ui->image_url_label->setVisible(state);
    ui->image_url_edit->setVisible(state);
}

void Options::on_advanced_settings_button_clicked() {
    PasswordForm form(settings_buffer_.passwords, this);
    if (form.exec() == QDialog::Accepted) {
        SetAdvancedSettingsVisible(true);
        ui->advanced_settings_button->setVisible(false);
    }
}
