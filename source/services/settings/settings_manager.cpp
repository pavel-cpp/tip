#include "settings_manager.h"

#include <QSqlRecord>

using std::string;

#include <QDebug>

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

    Database db(settings_.database, "settings_select");

    if(!db.connect()){
        return;
    }

    QString sql_request = SELECT_FONT_SETTINGS.arg(db.schema);
    db.query.prepare(sql_request);
    if(!db.query.exec()){
        assert(false);
    }
    for(auto& item: settings_.font_settings){
        if(!db.query.next()){
            break;
        }
        QSqlRecord rec = db.query.record();
        item.color = QColor(rec.value("color").toString());
        item.position.setX(rec.value("position_x").toDouble());
        item.position.setY(rec.value("position_y").toDouble());
        item.font.setFamily(rec.value("font").toString());
        item.font.setPixelSize(rec.value("size").toInt());
        item.font.setBold(rec.value("bold").toBool());
    }

    sql_request = SELECT_IMAGE.arg(db.schema);
    db.query.prepare(sql_request);
    db.query.exec();
    if(!db.query.next()){
        assert(false);
    }
    QSqlRecord rec = db.query.record();
    settings_.image.url = rec.value("url").toUrl();
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

    Database db(settings_.database, "settings_update");

    if(!db.connect()){
        return;
    }

    int index = 1;

    QString sql_request = UPDATE_FONT_SETTINGS.arg(db.schema);

    for(auto font: settings_.font_settings){
        db.query.prepare(sql_request);
        db.query.bindValue(0, font.font.family());
        db.query.bindValue(1, font.color);
        db.query.bindValue(2, font.position.x());
        db.query.bindValue(3, font.position.y());
        db.query.bindValue(4, font.font.pixelSize());
        db.query.bindValue(5, font.font.bold());
        db.query.bindValue(":id", index++);
        db.query.exec();
    }


    sql_request = UPDATE_IMAGE.arg(db.schema);
    db.query.prepare(sql_request);
    db.query.bindValue(":url", settings_.image.url);
    db.query.exec();

}
