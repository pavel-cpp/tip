#include "interfaces/mainwindow/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    QIcon icon("./resources/images/icon.png");
    w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
