#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QPointF>
#include <QFont>
#include <QColor>

struct Settings {
    QString fileIn;
    QPointF point[3];
    QFont font[3];
    QColor colors[3];
    unsigned long long startNumber;
    QString fileOut;
};

#endif // SETTINGS_H
