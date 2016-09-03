#ifndef CHATTHREAD_H
#define CHATTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

//! [0]
class ChatThread : public QThread
{
    Q_OBJECT

public:
    ChatThread(int socketDescriptor, QObject *parent);

    void run() Q_DECL_OVERRIDE;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
};
//! [0]

#endif // CHATTHREAD_H