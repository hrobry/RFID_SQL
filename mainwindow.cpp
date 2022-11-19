#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddevice.h"
#include "ui_adddevice.h"
//#include "ui_form.h"


#include <QtWidgets>

#include <QDebug>

#include <QAbstractButton>

//#include <QtSerialPort/QSerialPort>
//#include <QtSerialPort/QSerialPortInfo>
#include <QList>

#include <QDebug>





MainWindow::MainWindow( QWidget *parent)
     :QMainWindow(parent),
       ui(new Ui::MainWindow)



{

    ui->setupUi(this);







mysql=QSqlDatabase::addDatabase("QSQLITE","lulu");
QSqlQuery query(QSqlDatabase::database("lulu"));
mysql.setDatabaseName("C:/Users/monio/Desktop/RFID_project/SQL/name_db.db");
//mysql.setDatabaseName(":memory:");

qDebug()<<"db";
if(!mysql.open())
{

qDebug()<<"false";

}else
{
    ui->SQL_Box->toggle();
    qDebug()<<"true1";
}
if(query.exec("create table person "
          "(id integer primary key, "
          "firstname varchar(20), "
          "lastname varchar(30), "
          "age integer)"))
    qDebug()<<"true2";


    if(query.exec("create table  rf"
                   "(id integer  primary key ,"
                   "Name varchar(40) ,"
                   "LastName varchar(40), "
                  " RFID integer)"))




        qDebug()<< "true4";
    if(query.exec("insert into rf (id,Name,LastName,RFID) values"

             "  (1,'John','Kowalski',6363463)"))
        qDebug()<<"true5";

//mysql.close();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_ADD_button_clicked()
{
QSqlQuery query(QSqlDatabase::database("lulu"));
Name = ui->Name->text();
LastName = ui->LastName->text();
RFID=ui->RFID->text();
 ui->Name->clear();
 ui->LastName->clear();
 ui->RFID->clear();

 if(query.exec("insert into rf (Name,LastName,RFID) values ('"+Name+"','"+LastName+"','"+RFID+"')"))
     qDebug()<<"insertAdd";

}

void MainWindow::on_DELETE_button_clicked()
{
    QSqlQuery query(QSqlDatabase::database("lulu"));
RFID=ui->RFID->text();
query.exec("delete from rf where RFID ='"+RFID+"'");
ui->RFID->clear();
}

void MainWindow::on_CONFIGURE_Button_clicked()
{
    QSqlQuery query(QSqlDatabase::database("lulu"));
RFID = ui->RFID->text();
Name = ui->Name->text();
LastName = ui->LastName->text();
query.exec("delete from rf where RFID = '"+RFID+"'");
query.exec("insert into rf (Name,LastName,RFID) values ('"+Name+"','"+LastName+"','"+RFID+"')");
ui->Name->clear();
ui->LastName->clear();
ui->RFID->clear();
}

void MainWindow::on_SHOW_button_clicked()
{
QSqlQuery query(QSqlDatabase::database("lulu"));

//query.exec(" select from rf (")

        QSqlQueryModel *model = new QSqlQueryModel;

           model->setQuery("select id, Name, LastName, RFID  from rf",QSqlDatabase::database("lulu"));
           model->setHeaderData(0, Qt::Horizontal, tr("id"));
           model->setHeaderData(1, Qt::Horizontal, tr("Name"));
           model->setHeaderData(2, Qt::Horizontal, tr("LastName"));
           model->setHeaderData(3, Qt::Horizontal, tr("RFID"));
            // model->setHeaderData(1, Qt::Horizontal, tr("LastName"));
           QTableView *view = new QTableView;
           qDebug()<<model;
           view->setModel(model);
        view->setMaximumSize(600,300);

        view->setGeometry(2,2,500,500);

           view->show();
}

void MainWindow::on_ADD_Device_clicked()
{
adddevice.show();


}

void MainWindow::on_DELETE_Device_clicked()
{

}

void MainWindow::on_SEARCH_Device_clicked()
{
    QList<QSerialPortInfo> devices;  // deklaracja listy dostepnych urzadzen
    devices = QSerialPortInfo::availablePorts(); // zapelnienie listy sostepnymi urzadzeniami
  //  addToLogs( "Wyszukiwanie polaczen");
    for(int i = 0; i < devices.count(); i++) { // zapelnienie comboboxa lista urzadzen
     // qDebug() << devices.at(i).portName() << devices.at(i).description();
        ui->Device_Box->clear(); // wyczyszczenie comboboxa
        ui->Device_Box->addItem(devices.at(i).portName() +" \t" + devices.at(i).description()); // zapelnienie comboboxa lista urzadzen

                                         }
//addToLogs( "Wyszukiwanie polaczen");
}

void MainWindow::on_CONNECT_clicked()
{
    this->device = new QSerialPort;  // deklaracja portu szeregowego
    //device_Allow = true;
    QString portName = ui->Device_Box->currentText().split("\t").first(); // wybor urzadzenia z combo

    this->device->setPortName(portName); // ustawienie nazwy urzadzenia

    if(!device->isOpen()) { //  sprawdzenie czy port nie jest otwarty

      if(device->open(QSerialPort::ReadWrite)) { // otwarcie portu z nastepujacymi ustawieniami
            this->device->setBaudRate(QSerialPort::Baud9600);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);



           connect(this->device, SIGNAL(readyRead()), this, SLOT(readMessage()));
           qDebug()<<"CONNECTED";
           ui->RFID_Box->toggle(); //ustawienie znacznika polaczenia
          } else {
          qDebug()<<"NOT CONNECTED";
          }

      }
     else {
        qDebug()<<"NOT CONNECTED";
      return;

    // OTWÓRZ I SKONFIGURUJ PORT:
}
}

void MainWindow::on_DISCONNECT_clicked()
{

    if(this->device->isOpen()) {
         qDebug()<<"Connected";//ustawienie znacznika polaczenia
      this->device->close();
         if (ui->RFID_Box->isChecked())
         {
             ui->RFID_Box->toggle();
         }else
         {

         }

    } else {

      qDebug()<<"NOTConnected";//ustawienie znacznika polaczenia

    }

}
void MainWindow::readMessage()
{
QString line;

    while(this->device->canReadLine()) {  // jesli jest linia do przeczytania

        line = this->device->readLine();  // przeczytaj linie
qDebug()<<line;
ui->RFID->clear();
ui->RFID->insert(line);


}

}
