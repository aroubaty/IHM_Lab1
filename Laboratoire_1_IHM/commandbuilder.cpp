#include "commandbuilder.h"

CommandBuilder::CommandBuilder(QObject *parent) : QObject(parent)
{
}

QString CommandBuilder::getCommandLine(QString input, QString output, int start, int time){
    return "ffmpeg -i " + input + " -ss "+start+" -t "+time+" " + output;
}

QString CommandBuilder::getMeta(QString file){
    return QString("\"C:\\Users\\Anthony\\Google Drive\\Cours\\4eme HEIG\\IHM\\lab\\lab1\\ffmpeg\\bin\\ffprobe.exe\" " + file);
}
