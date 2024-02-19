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
#include <QApplication>
#include <QDebug>

#include <interfaces/mainwindow/mainwindow.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    QIcon icon("./resources/images/icon.png");
    w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
