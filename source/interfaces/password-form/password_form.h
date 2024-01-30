//
// Created by green on 30-Jan-24.
//

#ifndef TIP_PASSWORD_FORM_H
#define TIP_PASSWORD_FORM_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class password_form; }
QT_END_NAMESPACE

class password_form : public QDialog {
Q_OBJECT

public:
    explicit password_form(QWidget *parent = nullptr);

    ~password_form() override;

private:
    Ui::password_form *ui;
};


#endif //TIP_PASSWORD_FORM_H
