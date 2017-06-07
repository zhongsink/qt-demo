#include "widget.h"
#include "ui_widget.h"
#include "mytitlebar.h"
#include <QMovie>
#include <QLabel>
#include <QGroupBox>
#include <QToolButton>
#include <QVBoxLayout>
#include "personlist.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    MyTitleBar *m_titleBar = new MyTitleBar(this);
    connect( m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect( m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));

    ui->setupUi(this);
    // FramelessWindowHint属性设置窗口去除边框;
    // WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    //列表

    this->list=new personList(ui->listItem ,this->username);

    //背景图;
    QLabel* pBack = new QLabel(this);
    QMovie *movie = new QMovie();
    movie->setFileName(":/Resources/LoginWindow/head.png");
    movie->start();
    movie->stop();
    pBack->setMovie(movie);
    movie->start();
    pBack->move(0, 0);

    ui->footer->setPixmap(QPixmap(":/Resources/LoginWindow/foot.png"));

    //bar

    m_titleBar->move(0, 0);
    m_titleBar->raise();
    m_titleBar->setBackgroundColor(0, 0, 0 , true);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());




}

Widget::~Widget()
{
    delete ui;
}

void Widget::onButtonCloseClicked()
{
    close();
}


void Widget::onButtonMinClicked()
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
