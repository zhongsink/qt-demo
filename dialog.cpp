#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
#include <QMovie>
#include <QLabel>
#include "mytitlebar.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    MyTitleBar *m_titleBar = new MyTitleBar(this);
    connect( m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect( m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));

    // FramelessWindowHint属性设置窗口去除边框;
    // WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    ui->setupUi(this);

    //背景图;
    QLabel* pBack = new QLabel(this);
    QMovie *movie = new QMovie();
    movie->setFileName(":/Resources/LoginWindow/back.gif");
    movie->start();
    movie->stop();
    pBack->setMovie(movie);
    movie->start();
    pBack->move(0, 0);
    //注释;

    ui->usernameEdit->setPlaceholderText(QStringLiteral("QQ号码/手机/邮箱"));
    ui->passwordEdit->setPlaceholderText(QStringLiteral("密码"));

    ui->userHead->setPixmap(QPixmap(":/Resources/LoginWindow/HeadImage.png"));
    ui->loginState->setIcon(QIcon(":/Resources/LoginWindow/LoginState/state_online.png"));
    ui->loginState->setIconSize(QSize(13, 13));
    ui->moreAccountLogin->setIcon(QIcon(":/Resources/LoginWindow/more_accountlogin.png"));
    ui->moreAccountLogin->setIconSize(QSize(20, 20));
    ui->pButtongFlicker->setIcon(QIcon(":/Resources/LoginWindow/flicker.png"));
    ui->pButtongFlicker->setIconSize(QSize(20, 20));

    //bar

    m_titleBar->move(0, 0);
    m_titleBar->raise();
    m_titleBar->setBackgroundColor(0, 0, 0 , true);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleContent("qq 2018");

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if(!QString::compare(ui->usernameEdit->text(),"abc")&& !QString::compare(ui->passwordEdit->text(),"123456"))
        accept();
}


void Dialog::onButtonCloseClicked()
{
    close();
}


void Dialog::onButtonMinClicked()
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

