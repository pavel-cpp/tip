#pragma once

#include <QDialog>

#include <services/settings/settings_manager.h>
#include <QGraphicsScene>
#include <QGraphicsTextItem>


QT_BEGIN_NAMESPACE
namespace Ui { class TextPositionSelector; }
QT_END_NAMESPACE

class TextPositionSelector : public QDialog {
Q_OBJECT

public:
    explicit TextPositionSelector(QDialog *parent = nullptr);

    ~TextPositionSelector() override;

private slots:

    void on_button_box_accepted();

    void on_button_box_rejected();

private:
    Ui::TextPositionSelector *ui;

    QGraphicsScene scene_;
    std::array<QGraphicsTextItem, 3> items_;
    SettingsManager settings_manager_;
};
