#ifndef VIDEOCONVERTERFRAME_H
#define VIDEOCONVERTERFRAME_H

#include <QMainWindow>

namespace Ui {
class VideoConverterFrame;
}

class VideoConverterFrame : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoConverterFrame(QWidget *parent = 0);
    ~VideoConverterFrame();

private:
    Ui::VideoConverterFrame *ui;
};

#endif // VIDEOCONVERTERFRAME_H
