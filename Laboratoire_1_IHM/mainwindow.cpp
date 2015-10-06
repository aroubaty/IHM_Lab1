#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

void MainWindow::on_btnChooseOutputFile_clicked()
{
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
