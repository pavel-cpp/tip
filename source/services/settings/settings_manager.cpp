/*
    "Text Insertion Program (TIP)" is a software
    for client management and generating unique images for each client.
    Copyright (C) 2024  Pavel Remdenok

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "settings_manager.h"

#include <QSqlRecord>
#include <QString>
#include <QVariant>

using std::string;

// Qt
#include <QSqlQuery>

SettingsManager::SettingsManager(const QString &connection_name) {
    LoadFromIni(connection_name);
    LoadFromDatabase();
}

SettingsManager::Settings SettingsManager::GetSettings() {
    return settings_;
}

void SettingsManager::SetSettings(const SettingsManager::Settings &settings) {
    settings_ = settings;
}

void SettingsManager::Save(int type) {
    if(type == SaveType::SAVE_NONE){
        return;
    }
    if (~(type ^ SaveType::SAVE_GENERAL)) {
        settings_file_["general"]["path_to"] = settings_.output_folder.toStdString();
        settings_file_["general"]["theme"] = settings_.theme.toStdString();
    }

    if (~(type ^ SaveType::SAVE_DATABASE)) {
        settings_file_["database"]["host"] = settings_.database.host.toStdString();
        settings_file_["database"]["port"] = settings_.database.port;
        settings_file_["database"]["username"] = settings_.database.username.toStdString();
        settings_file_["database"]["password"] = settings_.database.password.toStdString();
        settings_file_["database"]["name"] = settings_.database.name.toStdString();
        settings_file_["database"]["schema"] = settings_.database.schema.toStdString();
    }

    settings_file_.save(SETTINGS_FILE_PATH_);

    if(!(~(type ^ SaveType::SAVE_DATABASE))){
        return;
    }
    database_.db.open();

    if (!database_.connect()) {
        return;
    }

    int index = 1;

    {
        QSqlQuery query(database_.db);
        QString sql_request = UPDATE_FONT_SETTINGS.arg(database_.schema);
        for (const auto &font: settings_.font_settings) {
            query.prepare(
                    sql_request
                            .arg("\'" + font.font.family() + "\'")
                            .arg("\'" + font.color.name(QColor::HexRgb) + "\'")
                            .arg(font.position.x())
                            .arg(font.position.y())
                            .arg(font.font.pixelSize())
                            .arg(font.font.bold() ? "true" : "false")
                            .arg(index++)
            );
            query.exec();
        }

        query.prepare(
                UPDATE_IMAGE
                        .arg(database_.schema)
                        .arg("\'" + settings_.image.url.toString() + "\'")
                        .arg("\'" + settings_.image.format + "\'")
        );
        query.exec();
    }

    database_.db.close();

}

void SettingsManager::ReloadSettings() {
    LoadFromIni(database_.db.connectionName());
    LoadFromDatabase();
}

void SettingsManager::LoadFromDatabase() {

    database_.db.open();

    if (!database_.connect()) {
        return;
    }

    {
        QSqlQuery query(database_.db);
        QString sql_request = SELECT_FONT_SETTINGS.arg(database_.schema);
        query.prepare(sql_request);
        if (!query.exec()) {
            assert(false);
        }
        for (auto &item: settings_.font_settings) {
            if (!query.next()) {
                break;
            }
            QSqlRecord rec = query.record();
            item.color = QColor(rec.value("color").toString());
            item.position.setX(rec.value("position_x").toDouble());
            item.position.setY(rec.value("position_y").toDouble());
            item.font.setFamily(rec.value("font").toString());
            item.font.setPixelSize(rec.value("size").toInt());
            item.font.setBold(rec.value("bold").toBool());
        }

        query.prepare(SELECT_IMAGE.arg(database_.schema));
        query.exec();
        if (!query.next()) {
            assert(false);
        }
        {
            QSqlRecord rec = query.record();
            settings_.image.url = rec.value("url").toUrl();
            settings_.image.format = rec.value("format").toString();
        }

        query.prepare(SELECT_PASSWORDS.arg(database_.schema));
        query.exec();
        assert(query.executedQuery() == SELECT_PASSWORDS.arg(database_.schema));

        settings_.passwords.passwords.clear();
        settings_.passwords.passwords.push_front("root");

        while (query.next()) {
            settings_.passwords.passwords.push_front(query.record().value("password").toString());
        }
    }

    database_.db.close();

}

void SettingsManager::LoadFromIni(const QString &connection_name) {
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

    database_ = Database(settings_.database, connection_name);
}
