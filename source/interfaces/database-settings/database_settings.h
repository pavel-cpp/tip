#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class database_settings; }
QT_END_NAMESPACE

class DatabaseSettings : public QDialog {
Q_OBJECT

public:
    explicit DatabaseSettings(QWidget *parent = nullptr);

    ~DatabaseSettings() override;

private:
    Ui::database_settings *ui;
};
