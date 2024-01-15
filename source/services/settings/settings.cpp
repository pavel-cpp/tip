#pragma once

#include "settings.h"
#include <fstream>
#include <stdexcept>

using std::ifstream;
using std::fstream;
using std::string;
using std::string_view;
using std::operator""s;

enum class TYPES{
    STRING,
    BOOL,
    INT
};

SettingsLoader::Settings SettingsLoader::GetSettings() {
    return settings_;
}

bool IsSection(string_view text) {
    return text.find('[') == string_view::npos;
}

string_view ParseSection(string_view text) {
    return text.substr(text.find('['), text.find(']'));
}

bool IsString(string_view text) {
    return text.find('\"') != string_view::npos;
}

[[maybe_unused]]  bool IsBool(string_view text) {
    return text.find("true") != string_view::npos || text.find("false") != string_view::npos;;
}

string ParseString(string_view text){
    return string(text.substr(text.find('\"'), text.rfind('\"')));
}

[[maybe_unused]]  bool ParseBool(string_view text){
    return text.find("true") != string_view::npos;
}

std::pair<string_view, string_view> ParseKeys(string_view text) {
    size_t eq_pos = text.find('=');
    return {text.substr(0, eq_pos), text.substr(eq_pos)};
}

void SettingsLoader::Load() {
    ifstream ini_file(settings_file_path_);
    if (!ini_file) {
        throw std::runtime_error("Ini file was deleted");
    }
    while (ini_file) {
        string buffer;
        std::getline(ini_file, buffer);
        if (buffer.empty()) {
            continue;
        }
        if (!IsSection(buffer)) {
            auto opt_to_val = ParseKeys(buffer);
            if (opt_to_val.first == "path_from") {
                settings_.input_image_path_ = QString::fromStdString(ParseString(opt_to_val.second));
            } else if (opt_to_val.first == "path_to") {
                settings_.output_folder_ = QString::fromStdString(ParseString(opt_to_val.second));
            }
        }
    }

    // TODO: Load from database
}

void SettingsLoader::SetSettings(const SettingsLoader::Settings &settings) {
    settings_ = settings;
}

void SettingsLoader::Save() {
    fstream file(settings_file_path_, std::ios::in);
    string file_content;
    while(file){
        string buffer;
        std::getline(file, buffer);
        if (buffer.empty()) {
            continue;
        }
        if (!IsSection(buffer)) {
            auto opt_to_val = ParseKeys(buffer);
            if (opt_to_val.first == "path_from") {
                file_content += opt_to_val.first;
                file_content += "="s + settings_.input_image_path_.toStdString();
            } else if (opt_to_val.first == "path_to") {
                file_content += opt_to_val.first;
                file_content += "="s + settings_.output_folder_.toStdString();
            }
        }
    }
    file.close();
    file.open(settings_file_path_, std::ios::out);
    file << file_content;
}
