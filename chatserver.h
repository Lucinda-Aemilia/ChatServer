#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "chatworker.h"

#include <QObject>
#include <QStringList>
#include <QThread>
#include <QTcpServer>
#include <QSignalMapper>

//! [0]
class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer(QObject *parent = 0);

public slots:

signals:
    void incameConnection(const qintptr &socketDescriptor);
    void disconnectedConnection(const qintptr &socketDescriptor);
    void readFromSocket(const qintptr& socketDescriptor, const QString& str);
    void writeToSocket(const qintptr& socketDescriptor, const QString& str);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

private:

    QVector<ChatWorker*> m_connections;
    QSignalMapper mapper;
};
//! [0]

#endif // CHATSERVER_H
