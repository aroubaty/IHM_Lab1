#include "commandbuilder.h"

CommandBuilder::CommandBuilder(QObject *parent) : QObject(parent)
{
}

QString CommandBuilder::getCommandLine(QString input, QString output, int start, int time){
    return "ffmpeg -i " + input + " -ss "+start+" -t "+time+" " + output;
}

QString CommandBuilder::getMeta(QString file){
    return "ffprobe -v quiet -print_format json -show_format -show_streams -byte_binary_prefix " + file;
}
