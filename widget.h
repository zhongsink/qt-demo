#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include "personlist.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString username;
    personList *list;
    void changeUsername(QString username){
        this->list->username=username;
        this->list->initMenu();
    }
private slots:
    void onButtonMinClicked();
    void onButtonCloseClicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
