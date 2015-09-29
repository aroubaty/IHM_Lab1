#include "videoconverterframe.h"
#include "ui_videoconverterframe.h"

VideoConverterFrame::VideoConverterFrame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideoConverterFrame)
{
    ui->setupUi(this);
}

VideoConverterFrame::~VideoConverterFrame()
{
    delete ui;
}
