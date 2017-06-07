#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>
#include <QString>
class QUdpSocket;

namespace Ui {
class Contact;
}

class Contact : public QWidget
{
    Q_OBJECT

public:
    explicit Contact(QWidget *parent = 0);
    QString username;
    void changeUsername(QString username);
    ~Contact();
private slots:
    void on_pushButton_clicked();
    void processPendingDatagram();
    void keyPressEvent(QKeyEvent  *event);
    void onButtonMinClicked();
    void onButtonCloseClicked();

private:
    QUdpSocket *receiver;
    QUdpSocket *sender;
    Ui::Contact *ui;
};

#endif // CONTACT_H
