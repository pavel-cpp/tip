#include "../headers/mainwindow.h"
#include <ui_mainwindow.h>

const std::string SETTINGS_FILE "./settings/settings.txt"

const std::string DATABASE_FILE "./database/database.db"

static const QSizeF dimensionFactor(1.686 * 1.15, 1.481 * 1.15);

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()) {
    ui->setupUi(this);

    QFile qssFile("./themes/White.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss = QLatin1String(qssFile.readAll());
    this->setStyleSheet(qss);
    qssFile.close();

    // Context Menu
    menu = std::make_unique<QMenu>(this);
    contextCopy = std::make_unique<QAction>(tr("Скопировать"), this);
    connect(contextCopy.get(), SIGNAL(triggered()), this, SLOT(on_copy_triggered()));
    menu->addAction(contextCopy.get());

    log = std::make_unique<Logger>("logs");
    log->info("Starting...");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_FILE);
    db.open();
    if (!db.isOpen()) log->warn("Database failed");
    query = std::make_unique<QSqlQuery>(db);
    query->exec("CREATE TABLE Clients(Name TEXT, Phone TEXT, Status TEXT, Number TEXT)");
    log->info("Database initialized");

    model = std::make_unique<QSqlTableModel>(this, db);
    model->setTable("Clients");
    model->select();

    log->info("Database model initialized");

    connect(model.get(), SIGNAL(dataChanged(
                                  const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(tableView_dataChanged(
                               const QModelIndex&)));

    ui->tableView->setModel(model.get());

    log->info("Database model set to table");

    log->info("Starting system initialize");
    this->init();
    log->info("System initialized");
    this->apply();
    size = image->size();
    current_size = size;

    for (int i = 0; i < model->rowCount(); i++)
        if (settings.startNumber == (unsigned) model->index(i, 0).data().toString().toInt())
            settings.startNumber++;

    ui->progressBar->setVisible(false);

    QSqlRecord record = model->record();
    record.setValue("Name", "");
    record.setValue("Phone", "");
    record.setValue("Status", "");
    unsigned ammount = 0;
    if (model->rowCount() <= 1) {
        Records_on_first_start dialog(&ammount);
        dialog.exec();
        ProgressBar progressBar;
        progressBar.show();
        progressBar.setMax(ammount);
        while (model->rowCount() < ammount) {
            record.setValue("Number", QString::fromStdString(std::to_string(model->rowCount() + 1)));
            model->insertRecord(-1, record);
            model->submitAll();
            progressBar.setValue(model->rowCount());
            QCoreApplication::processEvents();
        }
        progressBar.close();
    }

#ifndef GDB
    ui->tableView->setColumnHidden(3, true);
#endif
    log->info("Initializing done!");
}

void MainWindow::apply() {
    if(painter != nullptr) painter.reset();
    if(image != nullptr) image.reset();
    image = std::make_unique<QImage>(settings.fileIn);
    painter = std::make_unique<QPainter>(image.get());
    ui->screen->setPixmap(QPixmap::fromImage(*image));
    log->info("Image loaded!");
}

void MainWindow::init() {
    using std::ifstream;
    using std::string;
    using std::atoi;
    ifstream file(SETTINGS_FILE);
    if (!file.is_open()) {
        log->critical("Couldn't open settings file");
        exit(EXIT_FAILURE);
    }
    log->info("Settings opened successfully");
    string buffer;
    std::getline(file, buffer, '\n');
    log->info("Settings file in: " + buffer);
    settings.fileIn = QString::fromStdString(buffer);
    log->info("Reading positions...");
    for (int i = 0; i < 3; i++) {
        file >> buffer;
        log->info("X(" + std::to_string(i) + "): " + buffer);
        settings.point[i].setX(
                atoi(buffer.c_str())
        );
        file >> buffer;
        log->info("Y(" + std::to_string(i) + "): " + buffer);
        settings.point[i].setY(
                atoi(buffer.c_str())
        );
    }
    log->info("Reading font settings...");
    for (int i = 0; i < 3; i++) {
        log->info("Font " + std::to_string(i));
        std::getline(file, buffer, '\n');
        std::getline(file, buffer, '\n');
        log->info("Font name: " + buffer);
        QFont buf(QString::fromStdString(buffer), 10, QFont::Normal);
        file >> buffer;
        log->info("Font size: " + buffer);
        buf.setPixelSize(std::atoi(buffer.c_str()));
        file >> buffer;
        log->info("Font bold: " + buffer);
        if (buffer == "Bold") buf.setBold(true);
        settings.font[i] = buf;
        int color;
        file >> color;
        log->info("Font R: " + std::to_string(color));
        settings.colors[i].setRed(color);
        file >> color;
        log->info("Font G: " + std::to_string(color));
        settings.colors[i].setGreen(color);
        file >> color;
        log->info("Font B: " + std::to_string(color));
        settings.colors[i].setBlue(color);
    }
    file >> buffer;
    log->info("Statring number: " + buffer);
    settings.startNumber = std::strtoll(buffer.c_str(), nullptr, 10);
    std::getline(file, buffer, '\n');
    std::getline(file, buffer, '\n');
    log->info("Fileout: " + buffer);
    settings.fileOut = QString::fromStdString(buffer);
    file.close();
    log->info("File successfully read");
}

MainWindow::~MainWindow() {
    Options o(&settings);
    painter.reset();
    o.on_pushButton_4_clicked();
    log->info("Closed!");
}

void MainWindow::on_copy_triggered() {
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setImage(*image, QClipboard::Clipboard);
    ui->statusbar->showMessage("Картинка успешно скопирована в буфер обмена!");
    log->info("Image successfully copied");
}

void MainWindow::on_screen_customContextMenuRequested(const QPoint &pos) {
    log->info("Context menu requested");
    menu->popup(ui->screen->mapToGlobal(pos));
}

void MainWindow::draw() {
    apply();
    for (int i = 0; i < 3; i++) {
        if (items[i].isEmpty()) continue;
        painter->setFont(settings.font[i]);
        painter->setPen(settings.colors[i]);
        QPointF buff;
        buff.setX(settings.point[i].x()
                  - (((items[i].length()) * 0.25) * (settings.font[i].pixelSize()))
        );
        buff.setY(settings.point[i].y());
        painter->drawText(
                buff,
                items[i]
        );
        QImage scaled = image->scaled(current_size, Qt::KeepAspectRatio);
        ui->screen->setPixmap(QPixmap::fromImage(scaled));
    }
    log->info("Image drawn successfully");
}

void MainWindow::on_settings_triggered() {
    Options window(&settings);
    window.exec();
    apply();
    ui->statusbar->showMessage("Настройки сохранены!");
    log->info("Settngs saved");
}

void MainWindow::on_save_triggered() {
    image->save(settings.fileOut
                + "\\image_"
                + items[0]
                + ".jpg"
    );
    log->info("Image_"
              + items[0].toStdString()
              + " successfully saved!");
    ui->statusbar->showMessage("Image_"
                               + items[0]
                               + " успешно сохранена!");
    draw();
}

void MainWindow::on_print_triggered() {
    log->info("Print triggered");
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::NativeFormat);
    printer.setPrinterName("EPSON L3210 Series");
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Rejected) {
        log->info("Printer rejected");
        return;
    }
    log->info("Print started");
    QPainter painter(&printer);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();

    if (!selectedList.empty()) {
        int intervalX = 0, intervalY = -(image->height() * dimensionFactor.height() - 100);
        for (int i = 0; i < selectedList.size(); i++) {

            log->info("Image " + std::to_string(i) + " printed!");

            if (i % 12 == 0 && i != 0) {
                printer.newPage();
                intervalY = -(image->height() * dimensionFactor.height() - 100);
                intervalX = 0;
            }

            items[0] = QString::fromStdString(std::to_string(selectedList[i].row() + 1));
            items[1] = model->index(selectedList[i].row(), 0).data().toString();
            items[2] = model->index(selectedList[i].row(), 1).data().toString();
            draw();

            model->setData(
                    model->index(
                            selectedList[i].row(),
                            2
                    ),
                    "Распечатан"
            );

            if (i % 2 == 0) {
                intervalY += image->height() * dimensionFactor.height() + 100;
                intervalX = 0;
            }

            painter.drawPixmap(150 + intervalX, 150 + intervalY, image->width() * dimensionFactor.width(),
                               image->height() * dimensionFactor.height(),
                               QPixmap::fromImage(*image));
            intervalX += image->width() * dimensionFactor.width() + 100;
        }
    } else {
        model->setData(
                model->index(selectedList[0].row(), 3),
                "Распечатан"
        );
        painter.drawPixmap(150, 150, image->width() * dimensionFactor.width(),
                           image->height() * dimensionFactor.height(), QPixmap::fromImage(*image));
    }
    painter.end();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) {
    log->info("On table clicked");
    items[0] = QString::fromStdString(std::to_string(index.row() + 1));
    items[1] = model->index(index.row(), 0).data().toString();
    items[2] = model->index(index.row(), 1).data().toString();
    draw();
}

void MainWindow::on_textEdit_textChanged() {
    log->info("Searching " + ui->textEdit->toPlainText().toStdString());
    for (int i = 0; i <= model->rowCount(); i++) {
        for (int j = 0; j <= model->columnCount(); j++) {
            if (model->index(i, j).data().toString().contains(ui->textEdit->toPlainText())) {
                log->info("Found: " + model->index(i, j).data().toString().toStdString());
                if (ui->tableView->isRowHidden(i)) ui->tableView->showRow(i);
                break;
            } else {
                if (!ui->tableView->isRowHidden(i)) ui->tableView->hideRow(i);
            }
        }
    }
}

void MainWindow::on_show_db_triggered() {
    log->info("Database visible: true");
    ui->dock_db->setVisible(1);
}

void MainWindow::on_hide_db_triggered() {
    log->info("Database visible: false");
    ui->dock_db->setVisible(0);
}

void MainWindow::on_show_image_triggered() {
    log->info("Image visible: true");
    ui->dock_screen->setVisible(1);
}

void MainWindow::on_hide_image_triggered() {
    log->info("Image visible: false");
    ui->dock_screen->setVisible(0);
}

void MainWindow::on_imageScaleUp_triggered() {
    log->info("Image scaled up");
    current_size.setWidth(current_size.width() + 50);
    current_size.setHeight(current_size.height() + 50);
    draw();
}

void MainWindow::on_imageScaleDown_triggered() {
    log->info("Image scaled down");
    current_size.setWidth(current_size.width() - 50);
    current_size.setHeight(current_size.height() - 50);
    draw();
}

void MainWindow::on_saveSomeItems_triggered() {
    log->info("Save some items triggered!");
    unsigned amount;
    log->info("Records amount dialog opened!");
    RecordsAmmount dialog(&amount);
    if (dialog.exec() == QDialog::Rejected) {
        log->info("Rejected!");
        return;
    }
    log->info("Accepted! Ammount: " + std::to_string(amount));
    QList<int> list;
    log->info("Cells: ");
    for (int i = 0; i < model->rowCount() && list.size() < amount; ++i) {
        if (model->index(i, 0).data().toString().isEmpty() &&
            model->index(i, 1).data().toString().isEmpty()) {
            list.push_back(i);
            log->info(i);
        }
    }
    ui->progressBar->setMaximum(amount);
    int maximum = amount;
    ui->progressBar->setVisible(true);
    if (list.isEmpty()) {
        log->warn("List is empty!");
        return;
    }
    log->info("Inserting data: ");
    while (amount--) {
        if (list.isEmpty()) break;
        QSqlRecord record = model->record();
        record.setValue("Name", items[1]);
        record.setValue("Phone", items[2]);
        record.setValue("Status", " ");
        record.setValue("Number", model->index(list.first(), 3).data().toString());
        log->info("    Record: " + std::to_string(list.first()) + " " + items[1].toStdString() + " " +
                  items[2].toStdString());
        model->setRecord(list.first(), record);
        list.pop_front();
        ui->progressBar->setValue((maximum - (amount + 1)) % maximum);
    }
    ui->progressBar->setVisible(false);
    model->submitAll();
    ui->statusbar->showMessage("Запись успешно довалена!");
    log->info("Save some items end!");
}

void MainWindow::on_saveSomeImages_triggered() {
    log->info("Save some images triggered!");
    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    if (!selectedList.empty()) {
        ui->progressBar->setMaximum(selectedList.size());
        int maximum = selectedList.size();
        ui->progressBar->setVisible(true);
        for (int i = 0; i < selectedList.size(); i++) {
            QCoreApplication::processEvents();
            ui->progressBar->setValue((i + 1) % maximum);

            items[0] = QString::fromStdString(std::to_string(selectedList[i].row() + 1));
            items[1] = model->index(selectedList[i].row(), 0).data().toString();
            items[2] = model->index(selectedList[i].row(), 1).data().toString();
            draw();

            image->save(settings.fileOut
                        + "\\image_"
                        + items[0]
                        + ".jpg"
            );
            ui->statusbar->showMessage("Image_"
                                       + items[0]
                                       + " успешно сохранена!");
            log->info("    Image_"
                      + items[0].toStdString()
                      + " saved successfully!");
        }
    }

    ui->progressBar->setVisible(false);
    log->info("Save some images end!");
}

void MainWindow::tableView_dataChanged(const QModelIndex &Index) {
    log->info("Table view data changed!");
    log->info("Data: ");
    items[0] = QString::fromStdString(std::to_string(Index.row() + 1));
    for (int i = 0; i < 2; ++i) {
        items[i + 1] = model->index(Index.row(), i).data().toString();
        log->info("    " + items[i].toStdString());
    }
    draw();
}