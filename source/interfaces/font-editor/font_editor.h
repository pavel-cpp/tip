#pragma once

// Qt
#include <QColor>
#include <QDialog>

// Services
#include <services/database/models/font_settings_model.h>

namespace Ui {
    class FontEditor;
}

class FontEditor : public QDialog {
Q_OBJECT

public:
    explicit FontEditor(Models::FontSettings &font_settings, QWidget *parent = nullptr);

    ~FontEditor() override;

private slots:

    void on_red_slider_valueChanged(int value);

    void on_green_slider_valueChanged(int value);

    void on_blue_slider_valueChanged(int value);

    void on_font_combo_box_currentFontChanged(const QFont &font);

    void on_bold_check_box_stateChanged(int value);

    void on_size_spin_box_valueChanged(int value);

    void on_save_button_clicked();

private:

    void LoadFontSettings();

    Models::FontSettings font_settings_buffer_;

    Models::FontSettings &font_settings_;

    Ui::FontEditor *ui;
};
