#include "commandbuilder.h"

CommandBuilder::CommandBuilder(QObject *parent) : QObject(parent)
{
}

QString CommandBuilder::getCommandLine(QString input, QString output, int start, int time){
    return "ffmpeg -i \"" + input + "\" -ss " + QString::number(start) + " -t " + QString::number(time) + " \"" + output + "\"";
}
