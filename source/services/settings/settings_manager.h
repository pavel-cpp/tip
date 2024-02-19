#pragma once

// STDLIB
#include <array>
#include <cstddef>

// Qt
#include <QColor>
#include <QFont>
#include <QPointF>
#include <QString>

// Local
#include "const_options.h"
#include "ini-parser/inicpp.h"

// Services
#include <services/database/database.h>
#include <services/database/models.h>

class SettingsManager {
public:

    enum SaveType {
        SAVE_NONE = 0b000,
        SAVE_DATABASE = 0b001,
        SAVE_SYNCING = 0b010,
        SAVE_GENERAL = 0b100,
        SAVE_LOCAL = SAVE_DATABASE | SAVE_GENERAL,
        SAVE_ALL = SAVE_LOCAL | SAVE_SYNCING
    };

    struct Settings {
        const Constants consts;
        QString output_folder;
        QString theme;
        std::array<Models::FontSettings, 3> font_settings;
        Models::Database database;
        Models::Image image;
        Models::Passwords passwords;

        Settings &operator=(const Settings &other) {
            output_folder = other.output_folder;
            theme = other.theme;
            font_settings = other.font_settings;
            database = other.database;
            image = other.image;
            passwords = other.passwords;
            return *this;
        }

    };

    explicit SettingsManager(const QString &connection_name = "default");

    void ReloadSettings();

    Settings GetSettings();

    void SetSettings(const Settings &settings);

    void Save(int type = SaveType::SAVE_ALL);

private:

    void LoadFromDatabase();

    void LoadFromIni(const QString &connection_name);

    Database database_;

    Settings settings_;
    ini::IniFile settings_file_;

    const QString SELECT_FONT_SETTINGS = "SELECT * FROM %1.font_settings;";

    const QString UPDATE_FONT_SETTINGS = "UPDATE %1.font_settings SET font = %2, color = %3, position_x = %4, position_y = %5, size = %6, bold = %7 WHERE id = %8;";

    const QString SELECT_IMAGE = "SELECT url, format FROM %1.image WHERE id = 1;";

    const QString UPDATE_IMAGE = "UPDATE %1.image SET url = %2, format = %3 WHERE id = 1;";

    const QString SELECT_PASSWORDS = "SELECT * FROM %1.advanced_settings_passwords;";

    const std::string SETTINGS_FILE_PATH_ = "./settings/settings.ini";

};


