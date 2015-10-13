#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "commandbuilder.h"

#include <QFileDialog>
#include <QProcess>

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
    ui->txtInputFile->setText(fileName);

    // Display file properties
    QString command = "explorer.exe"; // TODO:Remplacer par CommandBuilder qui marche pas

    QProcess process;
    process.start(command);
    process.waitForFinished(-1);

    QString result = process.readAllStandardOutput();
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
