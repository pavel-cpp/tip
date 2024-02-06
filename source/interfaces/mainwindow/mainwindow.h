#pragma once

// Qt
#include <QMainWindow>
#include <QMenu>
#include <QSqlTableModel>
#include <QTableWidget>

// Services
#include <services/logger/logger.h>
#include <services/settings/settings_manager.h>
#include <services/text-painter/text_painter.h>

// Interfaces
#include <interfaces/options/options.h>

// STL
#include <array>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:

    void on_save_some_images_triggered();

    void on_copy_triggered();

    void on_settings_triggered();

    void on_save_image_triggered();

    void on_print_triggered();

    void on_database_search_textChanged();

    void on_show_database_triggered();

    void on_hide_database_triggered();

    void on_show_image_triggered();

    void on_hide_image_triggered();

    void on_database_table_view_clicked(const QModelIndex &);

    void on_image_scale_up_triggered();

    void on_image_scale_down_triggered();

    void on_refresh_database_action_triggered();

    void on_insert_single_record_triggered();

    void on_insert_same_records_triggered();

    void database_table_view_data_changed(const QModelIndex &index);

private:

    Logger log_ = Logger("logs");

    QSize current_image_size_;

    std::array<TextPainter::ContentTemplate, 3> items_;

    TextPainter text_painter_;
    SettingsManager settings_manager_;

    Database database_;
    std::unique_ptr<QSqlTableModel> table_model_;

    std::unique_ptr<Ui::MainWindow> ui;

    void ReDrawImage();

    void SetContents(const QModelIndex &index);

};
