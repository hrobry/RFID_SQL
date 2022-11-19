#ifndef ADDDEVICE_H
#define ADDDEVICE_H
#include <QMainWindow>
#include <QWidget>
#include <ui_adddevice.h>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE

namespace Ui { class adddevice;  }

QT_END_NAMESPACE


class AddDevice: public QWidget
{
    Q_OBJECT

public:

    AddDevice( QWidget *parent = nullptr);
    ~AddDevice();

    QString DeviceName, BaudRate , StopBits , DataBits , Parity, FlowControl;



private slots:
    void on_Ok_clicked();


void kombo();

void on_Devices_clicked();

private:



     Ui::adddevice *uii;
     QSqlDatabase data;
     QSqlQuery *Querry;
};

#endif // ADDDEVICE_H
