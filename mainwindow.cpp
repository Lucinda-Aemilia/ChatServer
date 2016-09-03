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

    connect(&m_server, SIGNAL(incameConnection(qintptr)),
            this, SLOT(incameConnection(qintptr)));

    if (!m_server.listen(m_address, m_port))
    {
        QMessageBox::critical(this, tr("Threaded Chat Server"),
                              tr("Unable to start the server: %1.")
                              .arg(m_server.errorString()));
        close();
        return;
    }
}

void MainWindow::incameConnection(const qintptr &socketDescriptor)
{
    m_connections.append(socketDescriptor);

    // 更新用户列表
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

void MainWindow::readSignInInfo()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
