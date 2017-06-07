#include "widget.h"
#include <QApplication>
#include "dialog.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Dialog dialog;                        // 新建MyDialog类对象
    char returnValue = dialog.exec();
    if(returnValue==QDialog::Accepted){   // 判断dialog执行结果
        Widget w;

        w.username=dialog.username;
        qDebug()<<w.username; // 如果是按下了“进入主界面”按钮，则显示主界面
        w.changeUsername(w.username);
        w.show();
        return a.exec();                    // 程序正常运行
    }
    else return 0;
}
