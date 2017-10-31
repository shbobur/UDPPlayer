#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QObject>
#include <QPixmap>

class ConnectionHandler : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionHandler(QObject *parent = nullptr);


signals:
    void newFrame(QPixmap);

public slots:
    void reconnectToHost();
};

#endif // CONNECTIONHANDLER_H
