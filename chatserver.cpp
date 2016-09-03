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
    ChatThread *thread = new ChatThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
//! [1]
