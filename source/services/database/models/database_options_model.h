#pragma once

#include <QString>

namespace Models {
    struct Database {
        QString host;
        uint16_t port;
        QString username;
        QString password;
        QString name;
        QString schema;
    };
}