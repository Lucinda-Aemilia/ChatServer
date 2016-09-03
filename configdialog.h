#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QtNetwork>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();
    QHostAddress getAddress() const { return m_address; }
    int getPort() const { return m_port; }

public slots:
    void changeIpAddress(const QString& address);
    void changePort(const int &port);

private slots:
    void on_hostComboBox_currentTextChanged(const QString &arg1);

    void on_portSpinBox_valueChanged(int arg1);

private:
    Ui::ConfigDialog *ui;
    QHostAddress m_address;
    int m_port;
};

#endif // CONFIGDIALOG_H
