#include "settings_manager.h"

#include <QSqlRecord>

using std::string;

SettingsManager::SettingsManager() {
    settings_file_.load(SETTINGS_FILE_PATH_);

    settings_.output_folder = QString::fromStdString(settings_file_["general"]["path_to"].as<string>());
    settings_.theme = QString::fromStdString(settings_file_["general"]["theme"].as<string>());

    settings_.database = {
            QString::fromStdString(settings_file_["database"]["host"].as<string>()),
            settings_file_["database"]["port"].as<uint16_t>(),
            QString::fromStdString(settings_file_["database"]["username"].as<string>()),
            QString::fromStdString(settings_file_["database"]["password"].as<string>()),
            QString::fromStdString(settings_file_["database"]["name"].as<string>()),
            QString::fromStdString(settings_file_["database"]["schema"].as<string>())
    };

    Database db(settings_.database);

    if(!db.connect()){
        return;
    }

    db.query.prepare(SELECT_FONT_SETTINGS);
    db.query.bindValue(":schema", db.schema);
    db.query.exec();
    QSqlRecord rec = db.query.record();
    for(auto& item: settings_.font_settings){
        item.color = QColor(db.query.value(rec.indexOf("color")).toString());
        item.text_position.setX(db.query.value(rec.indexOf("position_x")).toDouble());
        item.text_position.setY(db.query.value(rec.indexOf("position_y")).toDouble());
        item.font.setFamily(db.query.value(rec.indexOf("font")).toString());
        item.font.setPixelSize(db.query.value(rec.indexOf("size")).toInt());
        item.font.setBold(db.query.value(rec.indexOf("bold")).toBool());
        if(!db.query.next()){
            break;
        }
    }

    db.query.prepare(SELECT_IMAGE);
    db.query.bindValue(":schema", db.schema);
    db.query.exec();
    rec = db.query.record();
    settings_.image.url = db.query.value(rec.indexOf("url")).toUrl();
}

SettingsManager::Settings SettingsManager::GetSettings() {
    return settings_;
}

void SettingsManager::SetSettings(const SettingsManager::Settings &settings) {
    settings_ = settings;
}

void SettingsManager::Save() {
    settings_file_["general"]["path_to"] = settings_.output_folder.toStdString();
    settings_file_["general"]["theme"] = settings_.theme.toStdString();

    settings_file_["database"]["host"] = settings_.database.host.toStdString();
    settings_file_["database"]["port"] = settings_.database.port;
    settings_file_["database"]["username"] = settings_.database.username.toStdString();
    settings_file_["database"]["password"] = settings_.database.password.toStdString();
    settings_file_["database"]["name"] = settings_.database.name.toStdString();
    settings_file_["database"]["schema"] = settings_.database.schema.toStdString();

    settings_file_.save(SETTINGS_FILE_PATH_);

    Database db(settings_.database);

    if(!db.connect()){
        return;
    }

    int index = 1;
    for(auto font: settings_.font_settings){
        db.query.prepare(UPDATE_FONT_SETTINGS);
        db.query.bindValue(":schema", db.schema);
        db.query.bindValue(":id", index++);
        db.query.bindValue(0, font.font.family());
        db.query.bindValue(1, font.color);
        db.query.bindValue(2, font.text_position.x());
        db.query.bindValue(3, font.text_position.y());
        db.query.bindValue(4, font.font.pixelSize());
        db.query.bindValue(5, font.font.bold());
        db.query.exec();
    }

    db.query.prepare(UPDATE_IMAGE);
    db.query.bindValue(":schema", db.schema);
    db.query.bindValue(":url", settings_.image.url);
    db.query.exec();

}
