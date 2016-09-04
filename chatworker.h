#ifndef CHATWORKER_H
#define CHATWORKER_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

//! [0]
class ChatWorker : public QObject
{
    Q_OBJECT

public:
    ChatWorker(qintptr socketDescriptor, QObject *parent = NULL);

signals:
    void disconnectedConnection(const qintptr& _socketDescriptor);

public slots:
    void run();
    void socketDisconnectSlot();

signals:
    void error(QTcpSocket::SocketError socketError);


private:
    qintptr socketDescriptor;
    QTcpSocket* m_tcpSocket;
};
//! [0]

#endif // CHATWORKER_H
