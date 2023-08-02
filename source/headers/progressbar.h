#ifndef TIP_PROGRESSBAR_H
#define TIP_PROGRESSBAR_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ProgressBar; }
QT_END_NAMESPACE

class ProgressBar : public QWidget {
Q_OBJECT

public:
    explicit ProgressBar(QWidget *parent = nullptr);

    void setValue(unsigned val);

    void setMax(unsigned max);

    ~ProgressBar() override;

private:
    Ui::ProgressBar *ui;
};


#endif //TIP_PROGRESSBAR_H
