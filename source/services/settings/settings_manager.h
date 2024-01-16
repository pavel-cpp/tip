#pragma once

#include <array>
#include <cstddef>

#include <QString>
#include <QPointF>
#include <QFont>
#include <QColor>

#include "ini-parser/inicpp.h"

class SettingsManager {
private:

    struct TextModel {
        QPointF text_position;
        QFont font;
        QColor color;
    };

    struct DatabaseModel{
        QString host;
        uint16_t port;
        QString username;
        QString password;
        QString name;
        QString schema;
    };

    struct Settings {
        QString output_folder;
        std::array<TextModel, 3> text_configs;
        DatabaseModel database;
    };

public:

    SettingsManager();

    Settings GetSettings();

    void SetSettings(const Settings& settings);

    void Save();

private:

    Settings settings_;
    ini::IniFile settings_file_;

    const std::string settings_file_path_ = "./settings/settings.ini";

};


