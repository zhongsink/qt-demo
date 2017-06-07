#include <QSqlQuery>
#include <QObject>
#include "database.h"
#include <QDebug>

DataBase::DataBase(QObject *parent) :
    QObject(parent)
{
    this->_tableName="Users";
    this->opendatabase();

    this->insert();

//    this->GetValues();
}

DataBase::~DataBase()
{
    _db.close();
}

void DataBase::SetTableName(QString table)
{
    _tableName = table + ".db";
}

/*
    打开数据库.
*/
bool DataBase::opendatabase()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(_tableName);
    return _db.open();
}

/*
    插入函数.
    构造SQL插入语句.
*/
bool DataBase::insert()
//bool DataBase::insert(QString &table, QStringList &names, QStringList &values)
{
    QSqlQuery query;
    query.exec("create table Users (id int primary key, username varchar(20), password varchar(20) )");
    query.exec("insert into Users values(0, '819846546' , '123456')");
    query.exec("insert into Users values(1, '456487912' , '123456')");
    query.exec("insert into Users values(2, '123456789' , '123456')");

    return true;
}


QSqlQuery DataBase::GetValues()
{
    QSqlQuery query(QSqlDatabase::database());
    QString sql = QString("select * from ") + this->_tableName;
    query.exec(sql);
    return query;
//    while (query.next())
//    {
//        qDebug() << query.value(0).toInt() << query.value(1).toString()<< query.value(2).toString();
//    }
}
