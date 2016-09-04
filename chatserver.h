#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "chatworker.h"

#include <QObject>
#include <QStringList>
#include <QThread>
#include <QTcpServer>

//! [0]
class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer(QObject *parent = 0);

signals:
    void incameConnection(const qintptr &socketDescriptor);
    void disconnectedConnection(const qintptr &socketDescriptor);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

private:

};
//! [0]

#endif // CHATSERVER_H
