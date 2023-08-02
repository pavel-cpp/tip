#ifndef TIP_RECORDS_ON_FIRST_START_H
#define TIP_RECORDS_ON_FIRST_START_H

#include <QDialog>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class Records_on_first_start; }
QT_END_NAMESPACE

class Records_on_first_start : public QDialog {
Q_OBJECT

public:
    explicit Records_on_first_start(unsigned* ammount = nullptr, QDialog *parent = nullptr);

    ~Records_on_first_start() override;

public slots:

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();


private:

    unsigned* ammount;

    Ui::Records_on_first_start *ui;
};


#endif //TIP_RECORDS_ON_FIRST_START_H
