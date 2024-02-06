#pragma once

// Qt
#include <QDialog>

// Services
#include <services/database/models/passwords_model.h>

QT_BEGIN_NAMESPACE
namespace Ui { class PasswordForm; }
QT_END_NAMESPACE

class PasswordForm : public QDialog {
Q_OBJECT

public:
    explicit PasswordForm(const Models::Passwords &passwords, QWidget *parent = nullptr);

    ~PasswordForm() override;

private slots:

    void on_password_edit_returnPressed();

private:
    const Models::Passwords &passwords_;
    Ui::PasswordForm *ui;
};
