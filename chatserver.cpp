#include "chatserver.h"

#include <stdlib.h>

//! [0]
ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{

}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    QThread *thread = new QThread;
    ChatWorker* worker = new ChatWorker(socketDescriptor);
    m_connections.append(worker);
    worker->moveToThread(thread);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), worker, SLOT(run()));

    // mapper.setMapping(worker, worker);
    connect(worker, SIGNAL(readFromSocket(qintptr,QString)),
            this, SIGNAL(readFromSocket(qintptr,QString)));
    connect(this, SIGNAL(writeToSocket(qintptr,QString)),
            worker, SLOT(writeToSocket(qintptr,QString)));

    thread->start();
    emit incameConnection(socketDescriptor);
}
//! [1]
