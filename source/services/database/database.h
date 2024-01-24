#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <memory>
#include <QCoreApplication>

#include "models/database_options_model.h"

struct Database {
    QSqlDatabase db;
    QString schema;

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
            db.close();
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
