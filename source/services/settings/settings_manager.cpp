#include "settings_manager.h"

#include <fstream>
#include <stdexcept>

using std::string;

void SettingsManager::SetSettings(const SettingsManager::Settings &settings) {
    settings_ = settings;
}

void SettingsManager::Save() {
    settings_file_["general"]["path_to"] = settings_.output_folder.toStdString();

    settings_file_["database"]["host"] = settings_.database.host.toStdString();
    settings_file_["database"]["port"] = settings_.database.port;
    settings_file_["database"]["username"] = settings_.database.username.toStdString();
    settings_file_["database"]["password"] = settings_.database.password.toStdString();
    settings_file_["database"]["name"] = settings_.database.name.toStdString();
    settings_file_["database"]["schema"] = settings_.database.schema.toStdString();

    settings_file_.save(settings_file_path_);
}

SettingsManager::SettingsManager() {
    settings_file_.load(settings_file_path_);

    settings_.output_folder = QString::fromStdString(settings_file_["general"]["path_to"].as<string>());

    settings_.database = {
            QString::fromStdString(settings_file_["database"]["host"].as<string>()),
            settings_file_["database"]["port"].as<uint16_t>(),
            QString::fromStdString(settings_file_["database"]["username"].as<string>()),
            QString::fromStdString(settings_file_["database"]["password"].as<string>()),
            QString::fromStdString(settings_file_["database"]["name"].as<string>()),
            QString::fromStdString(settings_file_["database"]["schema"].as<string>())
    };

    // TODO(Pavel): Load from database
}

SettingsManager::Settings SettingsManager::GetSettings() {
    return settings_;
}
