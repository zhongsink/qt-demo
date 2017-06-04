#include "contact.h"
#include "ui_contact.h"
#include <QtNetwork>
#include <QKeyEvent>
#include <QDebug>
#include <QFile>

Contact::Contact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contact)
{
    receiver = new QUdpSocket(this);
    receiver->bind(23456, QUdpSocket::ShareAddress);
    connect(receiver, &QUdpSocket::readyRead, this, &Contact::processPendingDatagram);

    ui->setupUi(this);

    sender = new QUdpSocket(this);
}

Contact::~Contact()
{
    delete ui;
}
void Contact::keyPressEvent(QKeyEvent *event){
    if (event->type() == QEvent::KeyPress)
     {
        if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
        {
            this->on_pushButton_clicked();//按钮槽函数
        }
     }

}
void Contact::on_pushButton_clicked()
{
    QFile data("file.txt");

    QByteArray datagram = ui->textEdit->toPlainText().toUtf8();
    ui->listWidget->addItem(datagram);
    sender->writeDatagram(datagram.data(), datagram.size(),
                          QHostAddress("127.0.0.1"), 12345);
    if (data.open(QFile::WriteOnly | QIODevice::Append)) {
        QTextStream out(&data);
        out << datagram + "\r\n" ;
    }
    ui->textEdit->setText("");
    data.close();

}
void Contact::processPendingDatagram()
{
    // 拥有等待的数据报
    QFile data("file.txt");
    QByteArray datagram;
    while(receiver->hasPendingDatagrams())
    {

        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(receiver->pendingDatagramSize());

        // 接收数据报，将其存放到datagram中
        receiver->readDatagram(datagram.data(), datagram.size());

        ui->listWidget->addItem(datagram);
    }
    if (data.open(QFile::WriteOnly | QIODevice::Append)) {
        QTextStream out(&data);
        out << datagram +"\r\n";
    }
    data.close();
}

