#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnChooseInputFile_clicked();

    void on_btnChooseOutputFile_clicked();

    void on_timeEditStart_timeChanged(const QTime &time);

    void on_timeEditEnd_timeChanged(const QTime &time);

    void on_txtNameOutputFile_textChanged(const QString &arg1);

    void on_btnStart_clicked();

private:
    Ui::MainWindow *ui;
    QGridLayout* gridInputOutput;
    void updateCommand();
    void showTimeOverlapping();
};

#endif // MAINWINDOW_H
