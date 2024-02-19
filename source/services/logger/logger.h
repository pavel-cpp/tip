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

#pragma once

// STDLIB
#include <fstream>
#include <string>

// Qt
#include <QDate>
#include <QDir>
#include <QStringList>

class Logger : public std::ofstream {

public:

    explicit Logger(const std::string &path) : std::ofstream(
            path + "/log_" +
            std::to_string(QDate::currentDate().day()) + "_" +
            std::to_string(QDate::currentDate().month()) + "_" +
            std::to_string(QDate::currentDate().year()) + "_" + ".log",
            std::ios_base::app) {
        QStringList list = QDir((path + "/").c_str()).entryList(QDir::Files);
        QDate date;
        for (auto i: list) {
            if (!i.contains("log_")) continue;
            QStringList parse = i.split('_');
            date.setDate(parse[3].toInt(), parse[2].toInt(), parse[1].toInt());
            if (date.addDays(7) <= QDate::currentDate()) {
                system(("del " + path + "\\" + i.toStdString()).c_str());
            }
        }
    };

    static std::string Time() {
        return "[" + QTime::currentTime().toString().toStdString() + "]";
    }

    template<class T>
    void Critical(const T &message) {
        static_cast<std::ofstream &>(*this) << Logger::Time() << " [CRITICAL]: " << message << std::endl;
    }

    template<class T>
    void Info(const T &message) {
        static_cast<std::ofstream &>(*this) << Logger::Time() << " [INFO]: " << message << std::endl;
    }

    template<class T>
    void Warn(const T &message) {
        static_cast<std::ofstream &>(*this) << Logger::Time() << " [WARN]: " << message << std::endl;
    }

    template<class T>
    void Error(const T &message) {
        static_cast<std::ofstream &>(*this) << Logger::Time() << " [ERROR]: " << message << std::endl;
    }

    template<class T>
    Logger &operator<<(const T &object) {
        static_cast<std::ofstream &>(*this) << Logger::Time() << object << std::endl;
        return *this;
    }

};
