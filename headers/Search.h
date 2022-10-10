#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include <QSortFilterProxyModel>
#include "database_connection.h"
#include "PostProcessing.h"
#include <boost/algorithm/string/predicate.hpp>

namespace Ui {
class Search;
}


class cSqlTableQueryModel : public QSqlTableModel
{
    Q_OBJECT
public:
    cSqlTableQueryModel(QObject *parent = 0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setQueryAndStore(const QSqlQuery &query);
    bool setData(const QModelIndex &index);
    QVariant data(const QModelIndex& index, int role) const;
    QString mQueryStr;
    database_connection con;

private:
    public slots:

};

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(ReadInputInfo* , QWidget *parent = 0);
    ~Search();
    cSqlTableQueryModel mSqlTableQueryModel;
    PostProcessing *postProc;

public slots:
    void Init();

private slots:
    void ResiseTable(int);
    void TableQuery(QString);
    void on_double_click_table_item(QModelIndex);
    int getRowID(QStringList &lst, int column);
    void dateSearch();
    void comboSearch();

private:
    Ui::Search *ui;
    ReadInputInfo* m_pReadInputInfo;
};

#endif // SEARCH_H
