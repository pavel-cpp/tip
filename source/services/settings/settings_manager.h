#pragma once

#include <array>
#include <cstddef>

#include <QString>
#include <QPointF>
#include <QFont>
#include <QColor>

#include "ini-parser/inicpp.h"

#include <services/database/database.h>

#include <services/database/models.h>

class SettingsManager {
public:

    struct Settings {
        QString output_folder;
        QString theme;
        std::array<Models::FontSettings, 3> font_settings;
        Models::Database database;
        Models::Image image;
    };

    explicit SettingsManager(const QString& connection_name = "default");

    Settings GetSettings();

    void SetSettings(const Settings& settings);

    void Save();

private:

    QString connection_name_;

    Settings settings_;
    ini::IniFile settings_file_;

    const QString SELECT_FONT_SETTINGS = "SELECT * FROM %1.font_settings";

    const QString UPDATE_FONT_SETTINGS = "UPDATE %1.font_settings (font, color, position_x, position_y, size, bold) VALUES(?,?,?,?,?,?) WHERE id = :id";

    const QString SELECT_IMAGE = "SELECT url FROM %1.image WHERE id = 1";

    const QString UPDATE_IMAGE = "UPDATE %1.image SET url = :url WHERE id = 1;";

    const std::string SETTINGS_FILE_PATH_ = "./settings/settings.ini";

};


