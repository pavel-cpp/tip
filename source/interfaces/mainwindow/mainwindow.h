#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QPainter>
#include <QImage>
#include <QClipboard>
#include <QTableWidget>
#include <QProgressBar>
#include <QPrinter>
#include <QPrintDialog>

#include <QSqlDriver>
#include <QSqlDriverCreator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>

#include <services/settings/settings_manager.h>
#include <services/logger/logger.h>
#include <services/text-painter/text_painter.h>

#include <string>
#include <array>

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

    Logger log_ = Logger("logs");

    QSize current_image_size_;
    QSize default_image_size_;

    std::array<TextPainter::ContentTemplate, 3> items_;

    TextPainter text_painter_;
    SettingsManager settings_manager_;

    Database database_;
    std::unique_ptr<QSqlTableModel> table_model_;

    QMenu context_menu_ = QMenu(this);
    QAction context_action_copy_ = QAction(tr("Скопировать"), this);

    bool access_;

    std::unique_ptr<Ui::MainWindow> ui_;

    void ReDrawImage();

};

#endif // MAINWINDOW_H
