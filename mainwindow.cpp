#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configdialog.h"

MainWindow::MainWindow(const QHostAddress& address,
                       const int& port,
                       QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_address(address),
    m_port(port)
{
    ui->setupUi(this);

    ui->ipLabel->setText(QString("Current ip: %1")
                         .arg(m_address.toString()));
    ui->portLabel->setText(QString("Listening to port: %1")
                           .arg(port));

    qRegisterMetaType<qintptr>("qintptr");
    connect(&m_server, SIGNAL(incameConnection(qintptr)),
            this, SLOT(incameConnection(qintptr)));

    connect(&m_server, SIGNAL(disconnectedConnection(qintptr)),
            this, SLOT(socketDisconnectSlot(qintptr)));

    connect(&m_server, SIGNAL(readFromSocket(qintptr,QString)),
            this, SLOT(readFromSocket(qintptr,QString)));
    connect(this, SIGNAL(writeToSocket(qintptr,QString)),
            &m_server, SIGNAL(writeToSocket(qintptr,QString)));

    if (!m_server.listen(QHostAddress::Any, m_port))
    {
        QMessageBox::critical(this, tr("Threaded Chat Server"),
                              tr("Unable to start the server: %1.")
                              .arg(m_server.errorString()));
        close();
        return;
    }
}

void MainWindow::readFromSocket(const qintptr &socketDescriptor, const QString &str)
{
    qDebug() << "MainWindow::readFromSocket" << str;
    QStringList list(str.split('`'));
    if (list.at(0) == "QUIT")
    {
        if (m_connections.contains(socketDescriptor))
        {
            int index = m_connections.indexOf(socketDescriptor);
            m_connections.remove(index);
            m_usernames.remove(index);

            // 向所有QTcpSocket写用户列表
            QString str("LIST");
            for (int i = 0; i < m_connections.size(); i++)
            {
                str.append(QString("`%1`%2").arg(m_connections.at(i))
                           .arg(m_usernames.at(i)));
            }
            qDebug() << "MainWindow::incameConnection write to socket" << str;
            emit writeToSocket(-1, str);

            updateTableWidget();
        }
    }
    else if (list.at(0) == "USERNAME")
    {
        if (m_connections.contains(socketDescriptor))
        {
            int index = m_connections.indexOf(socketDescriptor);
            m_usernames[index] = list.at(1);

            // 向所有QTcpSocket写用户列表
            QString str("LIST");
            for (int i = 0; i < m_connections.size(); i++)
            {
                str.append(QString("`%1`%2").arg(m_connections.at(i))
                           .arg(m_usernames.at(i)));
            }
            qDebug() << "MainWindow::incameConnection write to socket" << str;
            emit writeToSocket(-1, str);

            // 更新用户列表
            // updateTableWidget();
            updateTableWidget();
        }
    }
    else if (list.at(0) == "INFO_TO")
    {
        qintptr descriptor = list.at(1).toInt();
        QString info(QString("INFO_FROM`%1`%2").arg(socketDescriptor)
                     .arg(list.at(2)));
        this->writeToSocket(descriptor, info);
    }
}

void MainWindow::incameConnection(const qintptr &socketDescriptor)
{
    m_connections.append(socketDescriptor);
    m_usernames.append("");


}

void MainWindow::updateTableWidget()
{
    ui->tableWidget->clear();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(2);
    QStringList labels;
    labels.append("Socket Descriptor");
    labels.append("Username");
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->setRowCount(m_connections.size());
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    for (int i = 0; i < m_connections.size(); i++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(
                    QString::number(m_connections.at(i)));

        ui->tableWidget->setItem(i, 0, newItem);

        newItem = new QTableWidgetItem(m_usernames.at(i));
        ui->tableWidget->setItem(i, 1, newItem);
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}

void MainWindow::socketDisconnectSlot(const qintptr &socketDescriptor)
{
    if (m_connections.contains(socketDescriptor))
    {
        int index = m_connections.indexOf(socketDescriptor);
        m_connections.remove(index);
        m_usernames.remove(index);

        // 向所有QTcpSocket写用户列表
        QString str("LIST");
        for (int i = 0; i < m_connections.size(); i++)
        {
            str.append(QString("`%1`%2").arg(m_connections.at(i))
                       .arg(m_usernames.at(i)));
        }
        qDebug() << "MainWindow::incameConnection write to socket" << str;
        emit writeToSocket(-1, str);

        // 更新用户列表
        updateTableWidget();
    }
}

void MainWindow::readSignInInfo()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
