#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    // find out name of this machine
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        ui->hostComboBox->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            ui->hostComboBox->addItem(name + QChar('.') + domain);
    }
    /*
    if (name != QLatin1String("localhost"))
        ui->hostComboBox->addItem(QString("localhost"));
    */
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback() &&
                ipAddressesList.at(i).toIPv4Address())
            ui->hostComboBox->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback() &&
                ipAddressesList.at(i).toIPv4Address())
            ui->hostComboBox->addItem(ipAddressesList.at(i).toString());
    }

    m_address = ipAddressesList.at(0);
    ui->portSpinBox->setValue(9065);
}

void ConfigDialog::changeIpAddress(const QString &address)
{
    m_address = QHostAddress(address);
}

void ConfigDialog::changePort(const int &port)
{
    m_port = port;
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_hostComboBox_currentTextChanged(const QString &arg1)
{
    changeIpAddress(arg1);
}

void ConfigDialog::on_portSpinBox_valueChanged(int arg1)
{
    changePort(arg1);
}
