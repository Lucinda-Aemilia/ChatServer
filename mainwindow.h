#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
#include <QTcpServer>
#include <QNetworkSession>

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

private:
    Ui::MainWindow *ui;
    QHostAddress m_address;
    int m_port;
};

#endif // MAINWINDOW_H
