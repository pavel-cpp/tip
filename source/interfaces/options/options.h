#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

#include <services/settings/settings_manager.h>

namespace Ui {
    class Options;
}

class Options : public QDialog {
Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);

    ~Options() override;

private slots:

    void on_path_to_edit_textEdited();

    void on_path_to_button_clicked();

    void on_theme_combo_box_currentIndexChanged(int);

    void on_change_button_ex_1_clicked();

    void on_change_button_ex_2_clicked();

    void on_change_button_ex_3_clicked();

    void on_change_text_position_button_clicked();

    void on_database_edit_button_clicked();

    void on_save_button_clicked();

private:

    SettingsManager settings_manager_;

    Ui::Options *ui;
};

#endif // OPTIONS_H
