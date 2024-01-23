#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <memory>

#include "models/database_options_model.h"

struct Database {
    QSqlDatabase db;
    QSqlQuery query;
    QString schema;

    explicit Database(Models::Database settings) {
        db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName(settings.host);
        db.setPort(settings.port);
        db.setUserName(settings.username);
        db.setPassword(settings.password);
        db.setDatabaseName(settings.name);
        query = QSqlQuery(db);
    }

    Database(const Database &database) {
        db = database.db;
        query = QSqlQuery(db);
        schema = database.schema;
    }

    Database &operator=(const Database &database) {
        Database tmp(database);
        swap(tmp);
    }

    void swap(Database &database) {
        std::swap(db, database.db);
        std::swap(query, database.query);
        std::swap(schema, database.schema);
    }

    bool connect(){
        return db.open();
    }

    void disconnect(){
        db.close();
    }

    explicit operator bool() const{
        return db.isOpen();
    }

};
