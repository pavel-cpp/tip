#include "text_position_selector.h"
#include "ui_text_position_selector.h"

TextPositionSelector::TextPositionSelector(std::array<Models::FontSettings, 3>& font_settings, QDialog *parent) :
        QDialog(parent), 
        ui(new Ui::TextPositionSelector),
        font_settings_(font_settings),
        scene_(this) {
    ui->setupUi(this);
    
    QImage img(Constants().source_image_path);
    scene_.setSceneRect(0, 0, img.width(), img.height());
    ui->graphics_view->setFixedSize(img.size());
    scene_.addPixmap(QPixmap::fromImage(img));

    items_[0].setPlainText("12345");
    items_[1].setPlainText("Имя Фамилия");
    items_[2].setPlainText("+1 (234)567-89-12");

    for (int i = 0; i < 3; ++i) {
        items_[i].setFont(font_settings_[i].font);
        items_[i].setDefaultTextColor(font_settings_[i].color);
        QPoint top_left = font_settings_[i].position;
        top_left.setX(top_left.x() - QFontMetrics(font_settings_[i].font).boundingRect(items_[i].toPlainText()).width() / 2);
        items_[i].setPos(top_left);
        items_[i].setFlag(QGraphicsTextItem::GraphicsItemFlag::ItemIsMovable);
        scene_.addItem(&items_[i]);
    }
    ui->graphics_view->setScene(&scene_);
}

TextPositionSelector::~TextPositionSelector() {
    delete ui;
}

void TextPositionSelector::on_button_box_rejected() {
    close();
}

void TextPositionSelector::on_button_box_accepted() {
    for (int i = 0; i < 3; ++i) {
        QPoint text_pos = items_[i].scenePos().toPoint();
        text_pos.setX(text_pos.x() + items_[i].sceneBoundingRect().width() / 2);
        font_settings_[i].position = text_pos;
    }
    close();
}
