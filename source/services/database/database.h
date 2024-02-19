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

// Qt
#include <QCoreApplication>
#include <QSqlDatabase>

// STDLIB
#include <memory>

// Local
#include "models/database_options_model.h"

struct Database {
    QSqlDatabase db;
    QString schema;

    Database() = default;

    explicit Database(Models::Database settings, const QString &connection_name = "default") {
        db = QSqlDatabase::addDatabase("QPSQL", connection_name);
        db.setHostName(settings.host);
        db.setPort(settings.port);
        db.setUserName(settings.username);
        db.setPassword(settings.password);
        db.setDatabaseName(settings.name);
        schema = settings.schema;
    }

    Database(const Database &database) {
        db = database.db;
        schema = database.schema;
    }

    Database &operator=(const Database &database) {
        Database tmp(database);
        swap(tmp);
        return *this;
    }

    ~Database() {
        if (db.isOpen()) {
            QString connection_name = db.connectionName();
            db.close();
            QSqlDatabase::removeDatabase(connection_name);
        }
    }

    void swap(Database &database) {
        std::swap(db, database.db);
        std::swap(schema, database.schema);
    }

    bool connect() {
        return db.open();
    }

    void disconnect() {
        db.close();
    }

    explicit operator bool() const {
        return db.isOpen();
    }

};
