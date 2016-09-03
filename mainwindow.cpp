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
}

MainWindow::~MainWindow()
{
    delete ui;
}
