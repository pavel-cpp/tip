#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QClipboard>
#include <QTableWidget>
#include <QProgressBar>
#include <QPrinter>
#include <QPrintDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>

#include "options.h"
#include "logger.h"
#include "progressbar.h"

#include <string>
#include <array>

//#define GDB

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void tableView_dataChanged(const QModelIndex&);

    void on_saveSomeImages_triggered();

    void on_saveSomeItems_triggered();

    void on_copy_triggered();

    void on_screen_customContextMenuRequested(const QPoint &);

    void on_settings_triggered();

    void on_save_triggered();

    void on_print_triggered();

    void on_textEdit_textChanged();

    void on_show_db_triggered();

    void on_hide_db_triggered();

    void on_show_image_triggered();

    void on_hide_image_triggered();

    void on_tableView_clicked(const QModelIndex &);

    void on_imageScaleUp_triggered();

    void on_imageScaleDown_triggered();

private:

    std::unique_ptr<Logger> log;

    Settings settings;
    std::unique_ptr<QPainter> painter;
    std::unique_ptr<QImage> image;
    QSize current_size, size;

    std::array<QString, 3> items;

    QSqlDatabase db;
    std::unique_ptr<QSqlQuery> query;
    std::unique_ptr<QSqlTableModel> model;

    std::unique_ptr<QMenu> menu;
    std::unique_ptr<QAction> contextCopy;

    bool access;

    std::unique_ptr<Ui::MainWindow> ui;

    void init();

    void apply();

    void draw();

};

#endif // MAINWINDOW_H
