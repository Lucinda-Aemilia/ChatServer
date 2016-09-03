#ifndef CHATWORKER_H
#define CHATWORKER_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

//! [0]
class ChatThread : public QObject
{
    Q_OBJECT

public:
    ChatThread(qintptr socketDescriptor, QObject *parent = NULL);

public slots:
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);


private:
    qintptr socketDescriptor;
    QTcpSocket* m_tcpSocket;
};
//! [0]

#endif // CHATWORKER_H
