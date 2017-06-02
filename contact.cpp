#include "contact.h"
#include "ui_contact.h"
#include <QtNetwork>

Contact::Contact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contact)
{
    receiver = new QUdpSocket(this);
    receiver->bind(12345, QUdpSocket::ShareAddress);
    connect(receiver, &QUdpSocket::readyRead, this, &Contact::processPendingDatagram);

    ui->setupUi(this);

    sender = new QUdpSocket(this);
}

Contact::~Contact()
{
    delete ui;
}

void Contact::on_pushButton_clicked()
{
    QByteArray datagram = ui->textEdit->toPlainText().toUtf8();
    ui->listWidget->addItem(datagram);
    sender->writeDatagram(datagram.data(), datagram.size(),
                          QHostAddress("127.0.0.1"), 23456);

}
void Contact::processPendingDatagram()
{
    // 拥有等待的数据报
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;

        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(receiver->pendingDatagramSize());

        // 接收数据报，将其存放到datagram中
        receiver->readDatagram(datagram.data(), datagram.size());
        //ui->label->setText(datagram);
        ui->listWidget->addItem(datagram);
    }
}

