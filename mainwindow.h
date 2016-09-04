#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chatserver.h"

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
#include <QTcpServer>
#include <QNetworkSession>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QHostAddress& address,
                        const int& port,
                        QWidget *parent = 0);
    ~MainWindow();


public slots:
    void readSignInInfo();
    void incameConnection(const qintptr& socketDescriptor);
    void socketDisconnectSlot(const qintptr& socketDescriptor);
    void readFromSocket(const qintptr& socketDescriptor, const QString& str);

signals:
    void writeToSocket(const qintptr& socketDescriptor, const QString& str);

protected:
    void updateTableWidget();

private:
    Ui::MainWindow *ui;
    QHostAddress m_address;
    int m_port;
    ChatServer m_server;
    QVector<qintptr> m_connections;
    QVector<QString> m_usernames;
};

#endif // MAINWINDOW_H
