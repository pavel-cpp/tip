#ifndef FONTCHANGER_H
#define FONTCHANGER_H

#include <QDialog>
#include <QColor>

namespace Ui {
    class FontChanger;
}

class FontChanger : public QDialog {
Q_OBJECT

public:
    explicit FontChanger(QFont *font, QColor *color, QWidget *parent = nullptr);

    ~FontChanger();

private slots:

    void on_red_valueChanged(int value);

    void on_redSpinBox_valueChanged(int arg1);

    void on_green_valueChanged(int value);

    void on_greenSpinBox_valueChanged(int arg1);

    void on_blue_valueChanged(int value);

    void on_blueSpinBox_valueChanged(int arg1);

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_bold_stateChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_save_clicked();

private:

    void changeFont();

    bool init;
    QFont font, *oldFont;
    QColor color, *oldColor;
    Ui::FontChanger *ui;
};

#endif // FONTCHANGER_H
