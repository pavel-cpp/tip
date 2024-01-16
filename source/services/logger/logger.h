#ifndef TIP_LOGGER_H
#define TIP_LOGGER_H

#include <fstream>
#include <string>
#include <QStringList>
#include <QDir>
#include <QDate>

class Logger : public std::ofstream {

public:

    Logger(const std::string &path) : std::ofstream(
            path + "/log_" +
            std::to_string(QDate::currentDate().day()) + "_" +
            std::to_string(QDate::currentDate().month()) + "_" +
            std::to_string(QDate::currentDate().year()) + "_" + ".log_",
            std::ios_base::app) {
        QStringList list = QDir((path + "/").c_str()).entryList(QDir::Files);
        QDate date;
        for(auto i : list) {
            if(!i.contains("log_")) continue;
            QStringList parse = i.split('_');
            date.setDate(parse[3].toInt(), parse[2].toInt(), parse[1].toInt());
            if(date.addDays(7) <= QDate::currentDate()) {
                system(("del " + path + "\\" + i.toStdString()).c_str());
            }
        }
    };

    std::string time() const {
        return "[" + QTime::currentTime().toString().toStdString() + "]";
    }

    template<class T>
    void critical(const T &message) {
        static_cast<std::ofstream &>(*this) << this->time() << " [CRITICAL]: " << message << std::endl;
    }

    template<class T>
    void info(const T &message) {
        static_cast<std::ofstream &>(*this) << this->time() << " [INFO]: " << message << std::endl;
    }

    template<class T>
    void warn(const T &message) {
        static_cast<std::ofstream &>(*this) << this->time() << " [WARN]: " << message << std::endl;
    }

    template<class T>
    void error(const T &message) {
        static_cast<std::ofstream &>(*this) << this->time() << " [ERROR]: " << message << std::endl;
    }

    template<class T>
    Logger &operator<<(const T &object) {
        static_cast<std::ofstream &>(*this) << this->time() << object << std::endl;
        return *this;
    }

};

#endif //TIP_LOGGER_H
