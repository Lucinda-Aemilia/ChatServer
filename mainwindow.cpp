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

    if (!m_server.listen(m_address, m_port))
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
            updateTableWidget();
        }
    }
}

void MainWindow::incameConnection(const qintptr &socketDescriptor)
{
    m_connections.append(socketDescriptor);

    // 更新用户列表
    updateTableWidget();
}

void MainWindow::updateTableWidget()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(m_connections.size());
    for (int i = 0; i < m_connections.size(); i++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(
                    QString::number(m_connections.at(i)));
        ui->tableWidget->setItem(i, 0, newItem);
    }
}

void MainWindow::socketDisconnectSlot(const qintptr &socketDescriptor)
{
    if (m_connections.contains(socketDescriptor))
    {
        int index = m_connections.indexOf(socketDescriptor);
        m_connections.remove(index);
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
