#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QFileSystemModel>
#include <QFileDialog>

#include <fstream>

#include "Settings.h"
#include "fontchanger.h"

namespace Ui {
    class Options;
}

class Options : public QDialog {
Q_OBJECT

public:
    explicit Options(Settings *settings, QWidget *parent = nullptr);

    ~Options();

public slots:

    void on_pushButton_4_clicked();

private slots:

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pathToRoot_textChanged(const QString &arg1);

    void on_pathTo_textChanged(const QString &arg1);

private:
    QFileSystemModel *model;
    Settings settings;
    Settings *buffer;
    Ui::Options *ui;
};

#endif // OPTIONS_H
