#include "chatserver.h"

#include <stdlib.h>

//! [0]
ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{

}
//! [0]

//! [1]
void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    QThread *thread = new QThread;
    ChatWorker* worker = new ChatWorker(socketDescriptor);
    worker->moveToThread(thread);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), worker, SLOT(run()));
    thread->start();
    emit incameConnection(socketDescriptor);
}
//! [1]
