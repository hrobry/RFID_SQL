#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>
#include <adddevice.h>

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow;   }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr);
    ~MainWindow();

    QString Name,LastName,RFID;

private slots:
    void on_ADD_button_clicked();

    void on_DELETE_button_clicked();

    void on_CONFIGURE_Button_clicked();

    void on_SHOW_button_clicked();

    void on_ADD_Device_clicked();

    void on_DELETE_Device_clicked();


    void on_SEARCH_Device_clicked();

    void on_CONNECT_clicked();

    void on_DISCONNECT_clicked();

    void readMessage();

private:

   Ui::MainWindow * ui;
   QSerialPort *device;
   QSqlDatabase mysql;
   QSqlQuery *query;
   AddDevice adddevice;


};
#endif // MAINWINDOW_H



