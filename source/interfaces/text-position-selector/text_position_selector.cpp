#include "text_position_selector.h"
#include "ui_text_position_selector.h"

TextPositionSelector::TextPositionSelector(QWidget *parent) :
        QWidget(parent), ui(new Ui::TextPositionSelector),
        settings_manager_("positions"){
    ui->setupUi(this);

    scene_.addPixmap(QPixmap::fromImage(QImage("./resources/images/image.png")));
    for(int i = 0; i < 3; ++i){
        auto settings = settings_manager_.GetSettings().font_settings;
        items_[i].setFont(settings[i].font);
        items_[i].setPos(settings[i].position);
        items_[i].setFlag(QGraphicsTextItem::GraphicsItemFlag::ItemIsMovable);
        scene_.addItem(&items_[i]);
    }
    items_[0].setPlainText("Number");
    items_[1].setPlainText("Name");
    items_[2].setPlainText("Phone number");
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
        auto settings = settings_manager_.GetSettings();
        QPoint text_pos = items_[i].pos().toPoint();
        text_pos.setX(items_[i].boundingRect().x() + items_[i].boundingRect().width() / 2);
        settings.font_settings[i].position = text_pos;
    }
    settings_manager_.SetSettings(settings);
    settings_manager_.Save();
    close();
}
