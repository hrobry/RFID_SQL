
#ifndef DATABASE_H
#define DATABASE_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;

    query.exec("create table Imie (id int primary key, "
                                     "Imie varchar(40), "
                                     "imiecount int)");

    query.exec("insert into Imie values(0, '<all>', 0)");
    query.exec("insert into Imie values(1, 'Przemo', 2)");


    query.exec("create table Nr (Nr int primary key, "
                                     "Nazwisko varchar(50), "
                                     "RFID int, "
                                     "JOB varchar(50))");

    query.exec("insert into albums values(1, 'Kubczynski', 1434, "
                       "'pielegniarz')");

    return true;
}

#endif

