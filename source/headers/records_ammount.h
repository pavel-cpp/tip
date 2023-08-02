#ifndef TIP_RECORDS_AMMOUNT_H
#define TIP_RECORDS_AMMOUNT_H

#include <QDialog>
#include <QFile>


QT_BEGIN_NAMESPACE
namespace Ui { class RecordsAmmount; }
QT_END_NAMESPACE

class RecordsAmmount : public QDialog {
Q_OBJECT

public:
    explicit RecordsAmmount(unsigned *amount, QWidget *parent = nullptr);

    ~RecordsAmmount() override;

private slots:

    void on_ok_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int value);

private:

    unsigned *amount;
    Ui::RecordsAmmount *ui;
};


#endif //TIP_RECORDS_AMMOUNT_H
