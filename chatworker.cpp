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
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readAll()));

    // 等待登录信息
    // m_tcpSocket
    emit establishedConnection();

}

void ChatWorker::writeToSocket(const qintptr &socketDescriptor, const QString &str)
{
    qDebug() << "ChatWorker::writeToSocket" << socketDescriptor << str;
    if (socketDescriptor == -1 || socketDescriptor == this->socketDescriptor)
        m_tcpSocket->write(str.toLocal8Bit());
}

void ChatWorker::readAll()
{
    QString str(m_tcpSocket->readAll());
    qDebug() << "ChatWorker::readAll()" << str;
    emit readFromSocket(socketDescriptor, str);
}

void ChatWorker::write(const QString &str)
{
    m_tcpSocket->write(str.toLocal8Bit());
}
