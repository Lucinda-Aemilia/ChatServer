#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "chatthread.h"

#include <QObject>
#include <QStringList>
#include <QTcpServer>

//! [0]
class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

private:

};
//! [0]

#endif // CHATSERVER_H
