#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class PasswordForm; }
QT_END_NAMESPACE

class PasswordForm : public QDialog {
Q_OBJECT

public:
    explicit PasswordForm(QWidget *parent = nullptr);

    ~PasswordForm() override;

private slots:
    void on_password_edit_returnPressed();

private:
    Ui::PasswordForm *ui;
};
