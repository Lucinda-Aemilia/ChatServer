#include "chatworker.h"

#include <QtNetwork>

//! [0]
ChatWorker::ChatWorker(qintptr socketDescriptor, QObject *parent)
    : QObject(parent), socketDescriptor(socketDescriptor)
{
}

void ChatWorker::socketDisconnectSlot()
{
    emit disconnectedConnection(socketDescriptor);
}

void ChatWorker::run()
{
    m_tcpSocket = new QTcpSocket;

    if (!m_tcpSocket->setSocketDescriptor(socketDescriptor)) {
        emit error(m_tcpSocket->error());
        return;
    }

    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnectSlot()));

    // 等待登录信息
    // m_tcpSocket

    /*
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << "hello";
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
//! [3] //! [4]

    tcpSocket.write(block);
    */

    /*
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
    */
}
//! [4]
