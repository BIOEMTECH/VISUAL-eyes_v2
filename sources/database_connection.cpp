/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file database_connection.cpp
///
///	@brief handles program's connection with the database
///
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "headers/database_connection.h"
#include <QLineEdit>

database_connection::database_connection()=default;

bool database_connection::enstablish_con()
{
    db = QSqlDatabase::addDatabase("QMYSQL"); // database driver
    db.setHostName("localhost"); //local host name
    db.setPort(3306);// connection port
    db.setDatabaseName("BET"); // name of database
    db.setUserName("root"); //username
    db.setPassword("11!!11"); // password

    if (!db.open())
        return false;

    return true;
}
