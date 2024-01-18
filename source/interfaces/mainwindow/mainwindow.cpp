#include "mainwindow.h"
#include <ui_mainwindow.h>

#include <QDebug>
#include "../../services/image-downloader/image_downloader.h"

const QString DATABASE_FILE = "./database/database.db";

const QSizeF dimensionFactor(1.686 * 1.15, 1.481 * 1.15);

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()) {
    ui->setupUi(this);

    QFile qssFile("./themes/dark.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss = QLatin1String(qssFile.readAll());
    this->setStyleSheet(qss);
    qssFile.close();
    
    connect(&context_action_copy_, SIGNAL(triggered()), this, SLOT(on_copy_triggered()));
    context_menu_.addAction(&context_action_copy_);
    
    log_.info("Starting...");

    db_ = QSqlDatabase::addDatabase("QPSQL");
    {
        auto db_settings = settings_manager_.GetSettings().database;
        db_.setHostName(db_settings.host);
        db_.setPort(db_settings.port);
        db_.setUserName(db_settings.username);
        db_.setPassword(db_settings.password);
        db_.setDatabaseName(db_settings.name);
    }
    db_.open();
    if (!db_.isOpen()) {
        qDebug() << "DatabaseModel is not opened" << endl;
    }
    db_query_ = QSqlQuery(db_);
    log_.info("DatabaseModel initialized");

    db_model_ = std::make_unique<QSqlTableModel>(this, db_);
    db_model_->setTable("main.clients");
    db_model_->select();

    // TODO(Pavel): Доделать сервис для БД ну или как то это вынести в модуль

    log_.info("DatabaseModel db_model_ initialized");

    connect(db_model_.get(), SIGNAL(dataChanged(
                                  const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(tableView_dataChanged(
                               const QModelIndex&)));

    ui->tableView->setModel(db_model_.get());
    ui->tableView->setColumnHidden(0, true);
    log_.info("DatabaseModel db_model_ set to table");

    if(!ImageDownloader::FetchImage("./resources/images/image.jpg", {"https://i.imgur.com/Oeh9w9D.png"})){
        qDebug() << "Downloading failed" << endl;
    }

    QImage image;

    image.load("./resources/images/image.jpg");

    text_painter_.SetImage(
            image
                    );

    current_image_size_ = default_image_size_ = text_painter_.GetOriginalImage().size();

    ui->progressBar->setVisible(false);

    ui->screen->setPixmap(text_painter_.GetResultPixmap());

    log_.info("Initializing done!");
}

MainWindow::~MainWindow() {
    log_.info("Closed!");
}

void MainWindow::on_copy_triggered() {
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setImage(text_painter_.GetResultImage(), QClipboard::Clipboard);
    ui->statusbar->showMessage("Картинка успешно скопирована в буфер обмена!");
    log_.info("Image successfully copied");
}

void MainWindow::on_screen_customContextMenuRequested(const QPoint &pos) {
    log_.info("Context context_menu_ requested");
    context_menu_.popup(ui->screen->mapToGlobal(pos));
}

void MainWindow::on_settings_triggered() {
//    Options window(&settings);
//    window.exec();
//    apply();
    ui->statusbar->showMessage("Настройки сохранены!");
    log_.info("Settngs saved");
}

void MainWindow::on_save_triggered() {
    text_painter_.GetResultImage().save(
            settings_manager_.GetSettings().output_folder
            + "image_"
            + items[0]
            + ".jpg"
            );
//    log_.info("Image_"
//               + items[0].toStdString()
//               + " successfully saved!");
    ui->statusbar->showMessage("image_"
                               + items[0]
                               + " успешно сохранена!");
}

void MainWindow::on_print_triggered() {
    /*log_.info("Print triggered");
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::NativeFormat);
    printer.setPrinterName("EPSON L3210 Series");
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Rejected) {
        log_.info("Printer rejected");
        return;
    }
    log_.info("Print started");
    QPainter painter(&printer);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();

    if (!selectedList.empty()) {
        int intervalX = 0, intervalY = -(image_.height() * dimensionFactor.height() - 100);
        for (int i = 0; i < selectedList.size(); i++) {

            log_.info("Image " + std::to_string(i) + " printed!");

            if (i % 12 == 0 && i != 0) {
                printer.newPage();
                intervalY = -(image_.height() * dimensionFactor.height() - 100);
                intervalX = 0;
            }

            items[0] = QString::fromStdString(std::to_string(selectedList[i].row() + 1));
            items[1] = db_model_->index(selectedList[i].row(), 0).data().toString();
            items[2] = db_model_->index(selectedList[i].row(), 1).data().toString();
            draw();

            db_model_->setData(
                    db_model_->index(
                            selectedList[i].row(),
                            2
                    ),
                    "Распечатан"
            );

            if (i % 2 == 0) {
                intervalY += image_.height() * dimensionFactor.height() + 100;
                intervalX = 0;
            }

            painter.drawPixmap(150 + intervalX, 150 + intervalY, image_.width() * dimensionFactor.width(),
                               image_.height() * dimensionFactor.height(),
                               QPixmap::fromImage(*image_));
            intervalX += image_.width() * dimensionFactor.width() + 100;
        }
    } else {
        db_model_->setData(
                db_model_->index(selectedList[0].row(), 3),
                "Распечатан"
        );
        painter.drawPixmap(150, 150, image_.width() * dimensionFactor.width(),
                           image_.height() * dimensionFactor.height(), QPixmap::fromImage(*image_));
    }
    painter.end();*/
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) {
    log_.info("On table clicked");
    items[0] = QString::fromStdString(std::to_string(index.row() + 1));
    items[1] = db_model_->index(index.row(), 0).data().toString();
    items[2] = db_model_->index(index.row(), 1).data().toString();
//    draw();
}

void MainWindow::on_textEdit_textChanged() {
    log_.info("Searching " + ui->textEdit->toPlainText().toStdString());
    for (int i = 0; i <= db_model_->rowCount(); i++) {
        for (int j = 0; j <= db_model_->columnCount(); j++) {
            if (db_model_->index(i, j).data().toString().contains(ui->textEdit->toPlainText())) {
                log_.info("Found: " + db_model_->index(i, j).data().toString().toStdString());
                if (ui->tableView->isRowHidden(i)) ui->tableView->showRow(i);
                break;
            } else {
                if (!ui->tableView->isRowHidden(i)) ui->tableView->hideRow(i);
            }
        }
    }
}

void MainWindow::on_show_db_triggered() {
    log_.info("DatabaseModel visible: true");
    ui->dock_db->setVisible(1);
}

void MainWindow::on_hide_db_triggered() {
    log_.info("DatabaseModel visible: false");
    ui->dock_db->setVisible(0);
}

void MainWindow::on_show_image_triggered() {
    log_.info("Image visible: true");
    ui->dock_screen->setVisible(1);
}

void MainWindow::on_hide_image_triggered() {
    log_.info("Image visible: false");
    ui->dock_screen->setVisible(0);
}

void MainWindow::on_imageScaleUp_triggered() {
    log_.info("Image scaled up");
    current_image_size_.setWidth(current_image_size_.width() + 50);
    current_image_size_.setHeight(current_image_size_.height() + 50);
//    draw();
}

void MainWindow::on_imageScaleDown_triggered() {
    log_.info("Image scaled down");
    current_image_size_.setWidth(current_image_size_.width() - 50);
    current_image_size_.setHeight(current_image_size_.height() - 50);
//    draw();
}

void MainWindow::on_saveSomeItems_triggered() {
    /*log_.info("Save some items triggered!");
    unsigned amount;
    log_.info("Records amount dialog opened!");
    RecordsAmmount dialog(&amount);
    if (dialog.exec() == QDialog::Rejected) {
        log_.info("Rejected!");
        return;
    }
    log_.info("Accepted! Ammount: " + std::to_string(amount));
    QList<int> list;
    log_.info("Cells: ");
    for (int i = 0; i < db_model_->rowCount() && list.size() < amount; ++i) {
        if (db_model_->index(i, 0).data().toString().isEmpty() &&
            db_model_->index(i, 1).data().toString().isEmpty()) {
            list.push_back(i);
            log_.info(i);
        }
    }
    ui->progressBar->setMaximum(amount);
    int maximum = amount;
    ui->progressBar->setVisible(true);
    if (list.isEmpty()) {
        log_.warn("List is empty!");
        return;
    }
    log_.info("Inserting data: ");
    while (amount--) {
        if (list.isEmpty()) break;
        QSqlRecord record = db_model_->record();
        record.setValue("Name", items[1]);
        record.setValue("Phone", items[2]);
        record.setValue("Status", " ");
        record.setValue("Number", db_model_->index(list.first(), 3).data().toString());
        log_.info("    Record: " + std::to_string(list.first()) + " " + items[1].toStdString() + " " +
                   items[2].toStdString());
        db_model_->setRecord(list.first(), record);
        list.pop_front();
        ui->progressBar->setValue((maximum - (amount + 1)) % maximum);
    }
    ui->progressBar->setVisible(false);
    db_model_->submitAll();
    ui->statusbar->showMessage("Запись успешно довалена!");
    log_.info("Save some items end!");*/
}

void MainWindow::on_saveSomeImages_triggered() {
//    log_.info("Save some images triggered!");
//    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
//    if (!selectedList.empty()) {
//        ui->progressBar->setMaximum(selectedList.size());
//        int maximum = selectedList.size();
//        ui->progressBar->setVisible(true);
//        for (int i = 0; i < selectedList.size(); i++) {
//            QCoreApplication::processEvents();
//            ui->progressBar->setValue((i + 1) % maximum);
//
//            items[0] = QString::fromStdString(std::to_string(selectedList[i].row() + 1));
//            items[1] = db_model_->index(selectedList[i].row(), 0).data().toString();
//            items[2] = db_model_->index(selectedList[i].row(), 1).data().toString();
//            draw();
//
//            image_.save(settings.fileOut
//                        + "\\editing_image_"
//                        + items[0]
//                        + ".jpg"
//            );
//            ui->statusbar->showMessage("Image_"
//                                       + items[0]
//                                       + " успешно сохранена!");
//            log_.info("    Image_"
//                       + items[0].toStdString()
//                       + " saved successfully!");
//        }
//    }
//
//    ui->progressBar->setVisible(false);
//    log_.info("Save some images end!");
}

void MainWindow::tableView_dataChanged(const QModelIndex &Index) {
    log_.info("Table view data changed!");
    log_.info("Data: ");
    items[0] = QString::fromStdString(std::to_string(Index.row() + 1));
    for (int i = 0; i < 2; ++i) {
        items[i + 1] = db_model_->index(Index.row(), i).data().toString();
        log_.info("    " + items[i].toStdString());
    }
//    draw();
}