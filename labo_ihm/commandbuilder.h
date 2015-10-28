#ifndef COMMANDBUILDER_H
#define COMMANDBUILDER_H

#include <QObject>

class CommandBuilder : public QObject
{
    Q_OBJECT
public:
    explicit CommandBuilder(QObject *parent = 0);

    static QString getCommandLine(QString input, QString output, int start, int time);

signals:

public slots:
};

#endif // COMMANDBUILDER_H
