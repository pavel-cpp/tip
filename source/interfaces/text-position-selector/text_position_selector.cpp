#include "text_position_selector.h"
#include "ui_text_position_selector.h"

TextPositionSelector::TextPositionSelector(QDialog *parent) :
        QDialog(parent), ui(new Ui::TextPositionSelector),
        settings_manager_("positions"),
        scene_(this)
        {
    ui->setupUi(this);
    QImage img("./resources/images/image.png");
    scene_.addPixmap(QPixmap::fromImage(img));
    scene_.setSceneRect(0, 0, img.width(), img.height());
    ui->graphics_view->setFixedSize(img.size());
    items_[0].setPlainText("Number");
    items_[1].setPlainText("Name");
    items_[2].setPlainText("Phone number");
    for(int i = 0; i < 3; ++i){
        auto settings = settings_manager_.GetSettings().font_settings;
        items_[i].setFont(settings[i].font);
        QPoint top_left = settings[i].position;
        top_left.setX(top_left.x() - QFontMetrics(settings[i].font).boundingRect(items_[i].toPlainText()).width() / 2);
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
    auto settings = settings_manager_.GetSettings();
    for(int i = 0; i < 3; ++i){
        QPoint text_pos = items_[i].scenePos().toPoint();

        text_pos.setX(text_pos.x() + items_[i].sceneBoundingRect().width() / 2);
        settings.font_settings[i].position = text_pos;
    }
    settings_manager_.SetSettings(settings);
    settings_manager_.Save();
    close();
}
