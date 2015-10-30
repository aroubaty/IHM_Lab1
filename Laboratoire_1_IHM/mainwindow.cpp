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
        ui->timeEditStart->setTime(QTime::fromMSecsSinceStartOfDay(0));
        ui->timeEditEnd->setTime(QTime::fromMSecsSinceStartOfDay(duration * 1000));

        ui->txtInputFile->setText(fileName);

        ui->txtInputFileProperties->setText(result);
        ui->txtFeedBack->setText("Valid input file");

    }
    else {
        ui->txtInputFileProperties->setText("Missing ffprobe process on your computer, impossible to load properties of file, If you have ffprobe binaries, put the directory in your PATH environnement.");
    }

    updateCommand();
}

void MainWindow::showTimeOverlapping() {

    QTime start = ui->timeEditStart->time();
    QTime end = ui->timeEditEnd->time();

    int overlapping = end.msecsSinceStartOfDay() - start.msecsSinceStartOfDay();
    ui->txtTimeOutputVideo->setText("Duration of output video : " + QTime::fromMSecsSinceStartOfDay(overlapping).toString());
}

void MainWindow::on_btnChooseOutputFile_clicked()
{
    QString directoryName = QFileDialog::getExistingDirectory(this);
    ui->txtOutputFile->setText(directoryName);
}

void MainWindow::on_timeEditStart_timeChanged(const QTime &time)
{
    showTimeOverlapping();
    updateCommand();
}

void MainWindow::on_timeEditEnd_timeChanged(const QTime &time)
{
    showTimeOverlapping();
    updateCommand();
}

void MainWindow::on_txtNameOutputFile_textChanged(const QString &arg1)
{
    updateCommand();
}

void MainWindow::on_btnStart_clicked()
{
    QMessageBox msg;

    if(ui->txtInputFile->text().isEmpty() || ui->txtInputFile->text().isNull()) {
        msg.setText("Please specifiy an input file");
        msg.exec();
        return;
    }

    if(ui->txtOutputFile->text().isEmpty() || ui->txtOutputFile->text().isNull()) {
        msg.setText("Please specifiy an output directory");
        msg.exec();
        return;
    }

    if(ui->txtNameOutputFile->text().isEmpty() || ui->txtNameOutputFile->text().isNull()) {
        msg.setText("Please specifiy a name for the output file (exemple : myVideo.MP4)");
        msg.exec();
        return;
    }

    if(ui->timeEditEnd->time().msecsSinceStartOfDay() - ui->timeEditStart->time().msecsSinceStartOfDay() < 0)
    {
        msg.setText("End Time smaller than start time, impossible to convert video. Please check.");
        msg.exec();
        return;
    }

    QStringList args;

    args << "-i" << ui->txtInputFile->text()
         << "-ss" << QString::number((int) ui->timeEditStart->time().msecsSinceStartOfDay() / 1000)
         << "-t" << QString::number((int) ui->timeEditEnd->time().msecsSinceStartOfDay() / 1000)
         << ui->txtOutputFile->text() + "/" + ui->txtNameOutputFile->text();

    msg.setText("The conversion will start in a terminal, please not close terminal frame. Click OK to start.");
    msg.exec();

    QProcess p;
    p.startDetached("ffmpeg", args);

}
