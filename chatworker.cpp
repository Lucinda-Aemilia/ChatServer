#include "chatworker.h"

#include <QtNetwork>

//! [0]
ChatThread::ChatThread(qintptr socketDescriptor, QObject *parent)
    : QObject(parent), socketDescriptor(socketDescriptor)
{
}
//! [0]

//! [1]
void ChatThread::run()
{
    m_tcpSocket = new QTcpSocket;

    if (!m_tcpSocket->setSocketDescriptor(socketDescriptor)) {
        emit error(m_tcpSocket->error());
        return;
    }

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
