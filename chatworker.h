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
    void establishedConnection();
    void disconnectedConnection(const qintptr& _socketDescriptor);
    void readFromSocket(const qintptr& _socketDescriptor, const QString&);

public slots:
    void run();
    void socketDisconnectSlot();
    void readAll();
    void write(const QString& str);
    void writeToSocket(const qintptr& socketDescriptor, const QString& str);

signals:
    void error(QTcpSocket::SocketError socketError);


private:
    qintptr socketDescriptor;
    QTcpSocket* m_tcpSocket;
};
//! [0]

#endif // CHATWORKER_H
