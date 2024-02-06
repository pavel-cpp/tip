#pragma once

// Qt
#include <QDialog>

// Services
#include <services/database/models/database_options_model.h>

QT_BEGIN_NAMESPACE
namespace Ui { class DatabaseSettings; }
QT_END_NAMESPACE

class DatabaseSettings : public QDialog {
Q_OBJECT

public:
    explicit DatabaseSettings(Models::Database &database_settings_, QWidget *parent = nullptr);

    ~DatabaseSettings() override;

private slots:

    void on_host_edit_textChanged(const QString &text);

    void on_port_edit_textChanged(const QString &text);

    void on_username_edit_textChanged(const QString &text);

    void on_password_edit_textChanged(const QString &text);

    void on_database_edit_textChanged(const QString &text);

    void on_schema_edit_textChanged(const QString &text);

    void on_test_button_clicked();

    void on_save_button_clicked();

private:

    Ui::DatabaseSettings *ui;

    Models::Database &database_settings_;
    Models::Database database_settings_buffer_;

};
