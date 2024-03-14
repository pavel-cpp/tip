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

/**
 * @class MainWindow
 * @brief The MainWindow class provides the main application window.
 *
 * This class provides a QMainWindow with various menu actions for managing the application's functionality.
 * It also manages the database and image display.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    /**
     * @brief Construct a new Main Window object
     *
     * @param parent Pointer to the parent QWidget. Default is nullptr.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Main Window object
     */
    ~MainWindow() override;

private slots:

    /**
     * @brief Slot for handling the save_some_images action.
     */
    void on_save_some_images_triggered();

    /**
     * @brief Slot for handling the copy action.
     */
    void on_copy_triggered();

    /**
     * @brief Slot for handling the settings action.
     */
    void on_settings_triggered();

    /**
     * @brief Slot for handling the save_image action.
     */
    void on_save_image_triggered();

    /**
     * @brief Slot for handling the print action.
     */
    void on_print_triggered();

    /**
     * @brief Slot for handling changes in the database search field.
     */
    void on_database_search_textChanged();

    /**
     * @brief Slot for handling the show_database action.
     */
    void on_show_database_triggered();

    /**
     * @brief Slot for handling the hide_database action.
     */
    void on_hide_database_triggered();

    /**
     * @brief Slot for handling the show_image action.
     */
    void on_show_image_triggered();

    /**
     * @brief Slot for handling the hide_image action.
     */
    void on_hide_image_triggered();

    /**
     * @brief Slot for handling clicks on the database table view.
     *
     * @param index The index of the clicked item.
     */
    void on_database_table_view_clicked(const QModelIndex &index);

    /**
     * @brief Slot for handling the image_scale_up action.
     */
    void on_image_scale_up_triggered();

    /**
     * @brief Slot for handling the image_scale_down action.
     */
    void on_image_scale_down_triggered();

    /**
     * @brief Slot for handling the refresh_database_action.
     */
    void on_refresh_database_action_triggered();

    /**
     * @brief Slot for handling the insert_single_record action.
     */
    void on_insert_single_record_triggered();

    /**
     * @brief Slot for handling the insert_same_records action.
     */
    void on_insert_same_records_triggered();

    /**
     * @brief Slot for handling the clear_database action.
     */
    void on_clear_database_triggered();

    /**
     * @brief Slot for handling changes in the database table view data.
     *
     * @param index The index of the changed item.
     */
    void database_table_view_data_changed(const QModelIndex &index);

private:

    Logger log_ = Logger("logs"); ///< Logger object for logging application events.

    QSize current_image_size_; ///< Current size of the displayed image.

    std::array<TextPainter::ContentTemplate, 3> items_; ///< Array of content templates for the TextPainter.

    TextPainter text_painter_; ///< TextPainter object for generating images.

    SettingsManager settings_manager_; ///< SettingsManager object for managing application settings.

    Database database_; ///< Database object for managing the application's database.

    std::unique_ptr<QSqlTableModel> table_model_; ///< QSqlTableModel object for managing the database table view.

    std::unique_ptr<Ui::MainWindow> ui; ///< Pointer to the UI object for this window.

    /**
     * @brief Redraw the displayed image.
     */
    void ReDrawImage();

    /**
     * @brief Set the contents of the TextPainter based on the given index.
     *
     * @param index The index of the item to use for setting the contents.
     */
    void SetContents(const QModelIndex &index);

};