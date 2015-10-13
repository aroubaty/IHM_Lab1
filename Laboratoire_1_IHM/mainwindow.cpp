#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "commandbuilder.h"

#include <QFileDialog>
#include <QProcess>
#include <QDebug>

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

void MainWindow::on_btnChooseInputFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);

    // Display file properties
    QString command = CommandBuilder::getMeta(fileName);

    QProcess process;
    process.start(command);

    QString result;

    if(process.waitForFinished(30000)) // True si le processus a bien démarré avant 30000 ms
    {

        qDebug("retour -> " + process.readAllStandardOutput());
        result = "lalal " + process.readAllStandardOutput();

        // TODO: Ici, il faut récupérer la durée de la vidéo et afficher son temps final dans le champ end_time...

    }
    else
        result = "Missing ffprobe process on your computer, impossible to load properties of file";

    ui->txtInputFile->setText(fileName);
    ui->txtInputFileProperties->setText(result);
}

void MainWindow::on_btnChooseOutputFile_clicked()
{
    QString directoryName = QFileDialog::getExistingDirectory(this);
    ui->txtOutputFile->setText(directoryName);
}

void MainWindow::on_timeEditStart_timeChanged(const QTime &time)
{
}

void MainWindow::on_timeEditEnd_timeChanged(const QTime &time)
{
}

void MainWindow::on_txtNameOutputFile_textChanged(const QString &arg1)
{
}

void MainWindow::updateCommmand() {
    QString command = "Une commande"; // TODO:Remplacer par CommandBuilder qui marche pas
    ui->txtCommandInvoked->setText(command);
}
