#pragma once

// Qt
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class RecordsAmountForm; }
QT_END_NAMESPACE

class RecordsAmountForm : public QDialog {
Q_OBJECT

public:
    explicit RecordsAmountForm(int &amount, QWidget *parent = nullptr);

    ~RecordsAmountForm() override;

private slots:

    void on_add_button_clicked();

private:

    int &amount_;

    Ui::RecordsAmountForm *ui;
};
