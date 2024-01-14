#include "options.h"
#include <ui_options.h>

const string SETTINGS_FILE "./settings/settings.txt";

Options::Options(Settings *settings, QWidget *parent) :
        buffer(settings),
        QDialog(parent),
        ui(new Ui::Options) {
    ui->setupUi(this);

    QFile qssFile("./themes/White.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss = QLatin1String(qssFile.readAll());
    this->setStyleSheet(qss);
    qssFile.close();

    this->settings.fileIn = buffer->fileIn;
    this->settings.fileOut = buffer->fileOut;
    this->settings.startNumber = buffer->startNumber;

    QLabel *labels[3] = {ui->example1, ui->example2, ui->example3};
    for (int i = 0; i < 3; i++) {
        this->settings.font[i] = buffer->font[i];
        this->settings.point[i] = buffer->point[i];
        this->settings.colors[i] = buffer->colors[i];
        labels[i]->setFont(this->settings.font[i]);
        QVariant var = this->settings.colors[i];
        labels[i]->setStyleSheet("color: " + var.toString());
    }
    ui->pathTo->setPlaceholderText(this->settings.fileOut);
    ui->pathToRoot->setPlaceholderText(this->settings.fileIn);
    ui->spinBox->setValue(settings->startNumber);
    QIcon icon("./icon.png");
    this->setWindowIcon(icon);
}

Options::~Options() {
    delete ui;
}

void Options::on_pushButton_5_clicked() {
    settings.fileIn = QFileDialog::getOpenFileName(0,
                                                   "Открыть исходный файл",
                                                   "",
                                                   "*.jpg",
                                                   nullptr
    );
    for (int i = 0; i < settings.fileIn.length(); i++) {
        if (settings.fileIn[i] == '/') settings.fileIn[i] = '\\';
    }
    ui->pathToRoot->setText(settings.fileIn);
}

void Options::on_pushButton_6_clicked() {
    settings.fileOut = QFileDialog::getExistingDirectory(this, tr("Выбрать место для сохранения"),
                                                         "",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    for (int i = 0; i < settings.fileOut.length(); i++) {
        if (settings.fileOut[i] == '/') settings.fileOut[i] = '\\';
    }
    ui->pathTo->setText(settings.fileOut);
}

// example_1
void Options::on_pushButton_clicked() {
    FontChanger window(&settings.font[0], &settings.colors[0]);
    window.exec();
    ui->example1->setFont(this->settings.font[0]);
    QVariant var = this->settings.colors[0];
    ui->example1->setStyleSheet("color: " + var.toString());
}

// example_2
void Options::on_pushButton_2_clicked() {
    FontChanger window(&settings.font[1], &settings.colors[1]);
    window.exec();
    ui->example2->setFont(this->settings.font[1]);
    QVariant var = this->settings.colors[1];
    ui->example2->setStyleSheet("color: " + var.toString());
}

// example_3
void Options::on_pushButton_3_clicked() {
    FontChanger window(&settings.font[2], &settings.colors[2]);
    window.exec();
    ui->example3->setFont(this->settings.font[2]);
    QVariant var = this->settings.colors[2];
    ui->example3->setStyleSheet("color: " + var.toString());
}


// Saving Settings
void Options::on_pushButton_4_clicked() {
    buffer->fileIn = settings.fileIn;
    buffer->fileOut = settings.fileOut;
    for (int i = 0; i < 3; i++) {
        buffer->font[i] = settings.font[i];
        buffer->point[i] = settings.point[i];
        buffer->colors[i] = settings.colors[i];
    }
    buffer->startNumber = settings.startNumber;

    std::ofstream file(SETTINGS_FILE);
    using std::endl;

    file << buffer->fileIn.toStdString() << endl;
    for (int i = 0; i < 3; i++)
        file << buffer->point[i].x()
             << ' ' << buffer->point[i].y() << endl;

    for (int i = 0; i < 3; i++)
        file << buffer->font[i].toString().toStdString().substr(0, buffer->font[i].toString().toStdString().find(','))
             << '\n'
             << buffer->font[i].pixelSize() << ' '
             << (buffer->font[i].bold() ? "Bold " : "Null ")
             << buffer->colors[i].red() << ' '
             << buffer->colors[i].green() << ' '
             << buffer->colors[i].blue() << endl;

    file << buffer->startNumber << endl
         << buffer->fileOut.toStdString();
    file.close();

    close();
}

void Options::on_pathToRoot_textChanged(const QString &arg1) {
    settings.fileIn = arg1;
}

void Options::on_pathTo_textChanged(const QString &arg1) {
    settings.fileOut = arg1;
}
