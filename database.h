#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QStringList>
#include <QSqlDatabase>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    void SetTableName(QString table);
    bool opendatabase();
    bool insert();

//    bool insert(QString &table, QStringList &names,QStringList &values);
    QSqlQuery GetValues();
private:
    QSqlDatabase _db;
    QString _tableName;

};
#endif // DATABASE_H
