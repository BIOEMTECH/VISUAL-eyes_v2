#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <QObject>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQueryModel>
#include <QMessageBox>

class database_connection
{
public:
    database_connection();
    QSqlDatabase db;

public slots:
    bool enstablish_con();
};

#endif // DATABASE_CONNECTION_H
