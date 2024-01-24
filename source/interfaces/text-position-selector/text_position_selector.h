#pragma once

#include <QWidget>

#include <services/settings/settings_manager.h>
#include <QGraphicsScene>
#include <QGraphicsTextItem>


QT_BEGIN_NAMESPACE
namespace Ui { class TextPositionSelector; }
QT_END_NAMESPACE

class TextPositionSelector : public QWidget {
Q_OBJECT

public:
    explicit TextPositionSelector(QWidget *parent = nullptr);

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
