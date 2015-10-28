#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "commandbuilder.h"

#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>

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
    QString command = "Une commande"; // TODO:Remplacer par CommandBuilder qui marche pas
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

    QString result;


    if(process.waitForFinished(3000)) // True si le processus a bien démarré avant 3 secondes
    {
        result = process.readAllStandardOutput();

        // Récupération des propriétés du fichier
        QJsonDocument document = QJsonDocument::fromJson(result.toUtf8());
        QJsonObject rootObject = document.object();


    }
    else {
        result = "Missing ffprobe process on your computer, impossible to load properties of file, If you have ffprobe binaries, put the directory in your PATH environnement.";
    }

    ui->txtInputFile->setText(fileName);
    ui->txtInputFileProperties->setText(result);

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
