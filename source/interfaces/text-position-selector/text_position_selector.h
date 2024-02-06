#pragma once

// Qt
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

// STL
#include <array>

// Services
#include <services/database/models/font_settings_model.h>
#include <services/settings/const_options.h>

QT_BEGIN_NAMESPACE
namespace Ui { class TextPositionSelector; }
QT_END_NAMESPACE

class TextPositionSelector : public QDialog {
Q_OBJECT

public:
    explicit TextPositionSelector(std::array<Models::FontSettings, 3> &font_settings, QDialog *parent = nullptr);

    ~TextPositionSelector() override;

private slots:

    void on_button_box_accepted();

    void on_button_box_rejected();

private:
    Ui::TextPositionSelector *ui;

    QGraphicsScene scene_;
    std::array<QGraphicsTextItem, 3> items_;

    std::array<Models::FontSettings, 3> &font_settings_;
};
