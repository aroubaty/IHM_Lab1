#include "commandbuilder.h"

CommandBuilder::CommandBuilder(QObject *parent) : QObject(parent)
{
}

QString CommandBuilder::getCommandLine(QString input, QString output, int start, int time){
    return "ffmpeg -i " + input + " -ss "+start+" -t "+time+" " + output;
}
