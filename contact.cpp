#include "contact.h"
#include "ui_contact.h"
#include <QtNetwork>
#include <QKeyEvent>
#include <QDebug>
#include <QFile>
#include "mytitlebar.h"
#include <QDateTime>
#include <QByteArray>

Contact::Contact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contact)
{
    MyTitleBar *m_titleBar = new MyTitleBar(this);
    connect( m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect( m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));

    // FramelessWindowHint属性设置窗口去除边框;
    // WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);



    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/Resources/LoginWindow/aaa.png"));
    ui->label_2->setPixmap(QPixmap(":/Resources/LoginWindow/aaa.png"));
    ui->label_3->setPixmap(QPixmap(":/Resources/LoginWindow/land.png"));
    ui->label_4->setPixmap(QPixmap(":/Resources/LoginWindow/HeadImage_small.png"));
    sender = new QUdpSocket(this);

    //bar
    m_titleBar->move(0, 0);
    m_titleBar->raise();
    m_titleBar->setBackgroundColor(144, 144, 144 , true);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
}

Contact::~Contact()
{
    delete ui;
}
void Contact::changeUsername(QString username){
    this->username=username;
    int port=this->username=="123456789"? 23456: 12345;
    receiver = new QUdpSocket(this);
    receiver->bind(port, QUdpSocket::ShareAddress);
    connect(receiver, &QUdpSocket::readyRead, this, &Contact::processPendingDatagram);
    if(this->username!="123456789"){
        ui->label_6->setText(".");
    }
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
    int port=this->username=="123456789"? 12345: 23456;
    QString username= this->username!="123456789"? "张三": ". ";
    QByteArray datagram = ui->textEdit->toPlainText().toUtf8();
    ui->listWidget->addItem(username + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+ "\r\n  " +datagram);
    sender->writeDatagram(datagram.data(), datagram.size(),
                          QHostAddress("127.0.0.1"), port);
    if (data.open(QFile::WriteOnly | QIODevice::Append)) {
        QTextStream out(&data);
        out << username+ QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+ "\r\n  " +datagram + "\r\n" ;
    }
    ui->textEdit->setText("");
    data.close();

}
void Contact::processPendingDatagram()
{
    // 拥有等待的数据报
    QFile data("file.txt");
    QByteArray datagram;
    QString username= this->username =="123456789"? "张三": ". ";
    while(receiver->hasPendingDatagrams())
    {

        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(receiver->pendingDatagramSize());

        // 接收数据报，将其存放到datagram中
        receiver->readDatagram(datagram.data(), datagram.size());

        ui->listWidget->addItem(username+ QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+ "\r\n  "+ datagram);
    }
    if (data.open(QFile::WriteOnly | QIODevice::Append)) {
        QTextStream out(&data);
        out << username+ QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+ "\r\n  "+ datagram +"\r\n";
    }
    data.close();
}

void Contact::onButtonCloseClicked()
{
    close();
}


void Contact::onButtonMinClicked()
{
    if (Qt::Tool == (windowFlags() & Qt::Tool))
    {
        hide();    //设置了Qt::Tool 如果调用showMinimized()则窗口就销毁了
    }
    else
    {
        showMinimized();
    }
}
