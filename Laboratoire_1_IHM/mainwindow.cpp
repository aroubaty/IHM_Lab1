#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "commandbuilder.h"

#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJSonArray>
#include <QJsonValue>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gridInputOutput;
}

void MainWindow::updateCommand() {

    QString command = CommandBuilder::getCommandLine(
                ui->txtInputFile->text(),
                ui->txtOutputFile->text() + "/" + ui->txtNameOutputFile->text(),
                (int) ui->timeEditStart->time().msecsSinceStartOfDay() / 1000,
                (int) ui->timeEditEnd->time().msecsSinceStartOfDay() / 1000);

    ui->txtCommandInvoked->setText(command);
}

void MainWindow::on_btnChooseInputFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);

    // Display file properties
    QString command = "ffprobe";

    QProcess process;

    // Ces paramètres permettent de récupérer les propriétés du fichier au format JSON, plus simple à parser
    QStringList args;
    args
            << "-v"
            << "quiet"
            << "-print_format"
            << "json"
            << "-show_format"
            << "-show_streams"
            << "-byte_binary_prefix"
            << fileName;

    process.start(command, args);

    if(process.waitForFinished(3000)) // True si le processus a bien démarré avant 3 secondes
    {        

        QString result = process.readAllStandardOutput();

        // Récupération des propriétés du fichier
        QJsonDocument document = QJsonDocument::fromJson(result.toUtf8());
        QJsonObject rootObject = document.object();

        // Si ça n'est pas un fichier vidéo, on met un feedback d'erreur
        if(rootObject.isEmpty()) {
            ui->txtFeedBack->setText("Invalid Video File");
            return;
        }


        QJsonArray streams = rootObject["streams"].toArray();
        QJsonObject firstStream = streams.at(0).toObject();

        double duration = firstStream["duration"].toString().toDouble();

        // Affichage de la durée et mise à jour du champ time end
        ui->timeEditEnd->setTime(QTime::fromMSecsSinceStartOfDay(duration * 1000));

        ui->txtInputFile->setText(fileName);


        ui->txtInputFileProperties->setText("Propriétés du fichier à mettre");


        ui->txtFeedBack->setText("Valid input file");

    }
    else {
        ui->txtInputFileProperties->setText("Missing ffprobe process on your computer, impossible to load properties of file, If you have ffprobe binaries, put the directory in your PATH environnement.");
    }

    updateCommand();
}

void MainWindow::on_btnChooseOutputFile_clicked()
{
    QString directoryName = QFileDialog::getExistingDirectory(this);
    ui->txtOutputFile->setText(directoryName);
}

void MainWindow::on_timeEditStart_timeChanged(const QTime &time)
{
    updateCommand();
}

void MainWindow::on_timeEditEnd_timeChanged(const QTime &time)
{
    updateCommand();
}

void MainWindow::on_txtNameOutputFile_textChanged(const QString &arg1)
{
    updateCommand();
}

void MainWindow::on_btnStart_clicked()
{
    QStringList args;

    args << "-i" << "/" + ui->txtInputFile->text().replace(":", "")
         << "-ss" << QString::number((int) ui->timeEditStart->time().msecsSinceStartOfDay() / 1000)
         << "-t" << QString::number((int) ui->timeEditEnd->time().msecsSinceStartOfDay() / 1000)
         << "/" + ui->txtOutputFile->text().replace(":","") + "/" + ui->txtNameOutputFile->text();

    QProcess p;
    p.startDetached("ffmpeg", args);

    /* On attend que la conversion soit finie */
    p.waitForFinished(-1);
}
