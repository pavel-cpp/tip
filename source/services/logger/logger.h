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
