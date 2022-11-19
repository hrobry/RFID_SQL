#include "adddevice.h"
#include "ui_adddevice.h"

#include <QWidget>

#include <QDebug>
#include <QVector>

#include <QAbstractButton>
#include <QWidget>
#include <QTableView>
  AddDevice::AddDevice(QWidget *parent)
       :QWidget(parent),
         uii(new Ui::adddevice)
{
 uii->setupUi(this);



 data=QSqlDatabase::addDatabase("QSQLITE","lala");
 QSqlQuery Query(QSqlDatabase::database("lala"));
 data.setDatabaseName("C:/Users/monio/Desktop/RFID_project/SQL/CommDevice_db.db");
 //mysql.setDatabaseName(":memory:");

 qDebug()<<"db_Devices";
 if(!data.open())
 {

 qDebug()<<"false_Devices";

 }else
 {
     uii->SQLcheckBox->toggle();
     qDebug()<<"true_Devices";
 }

 if(Query.exec("(create table if not exist device "
           ",id integer primary key, "
           " DeviceName varchar(20), "
           "BaudRate varchar(30), "
               "StopBits varchar(30), "
               "DataBits varchar(30), "
               "Parity varchar(30), "
               "FlowControl varchar(30)) "))

     qDebug()<<"true2";

 if(Query.exec("create table  ddd"
                "(id integer  primary key ,"
                "Name varchar(40) ,"
                "LastName varchar(40), "
               " RFID integer)"))
qDebug()<<"true70";

     if(Query.exec("insert into device (id,DeviceName,BaudRate,StopBits,DataBits,Parity,FlowControl) values"

              "  (1,'default','Baud9600','OneStop','Data8','NoParity','NoFlowControl')"))
         qDebug()<<"true5";


kombo();

//data.close();
}
 AddDevice::~AddDevice()
  {
      delete uii;
  }

void AddDevice::kombo()

{


   // QVector<QString> nums{"Baud1200","Baud2400","Baud4800","Baud9600","Baud19200","Baud38400","Baud57600","Baud115200","UnknownBaud"};

    QString f[9]= {"Baud1200","Baud2400","Baud4800","Baud9600","Baud19200","Baud38400","Baud57600","Baud115200","UnknownBaud"};
    for(int i =  0;i<9;i++){
    uii->BaudRateBox->addItem(f[i]);
   // qDebug()<<f[i];
    }
    QString d[6]= {"NoParity","EvenParity","OddParity","SpaceParity","MarkParity","UnknownParity"};
    for(int i =  0;i<6;i++){
    uii->ParityBox->addItem(d[i]);
  //  qDebug()<<d[i];
    }

    QString e[5]= {"Data5","Data6","Data7","Data8","UnknownDataBits"};
    for(int i =  0;i<5;i++){
    uii->DataBitsBox->addItem(e[i]);
   // qDebug()<<e[i];
    }
    QString g[4]= {"NoFlowControl","HardwareControl","SoftwareControl","UnknownFlowControl"};
    for(int i =  0;i<4;i++){
    uii->FlowControlBox->addItem(g[i]);
   // qDebug()<<g[i];
    }

    QString h[4]= {"NoFlowControl","HardwareControl","SoftwareControl","UnknownFlowControl"};


    for(int i =  0;i<4;i++){
    uii->StopBitsBox->addItem(h[i]);
   // qDebug()<<h[i];
    }

}


void AddDevice::on_Ok_clicked()
{

    QSqlQuery Query(QSqlDatabase::database("lala"));
   DataBits= uii->DataBitsBox->currentText();

   Parity = uii->ParityBox->currentText();

   FlowControl = uii->FlowControlBox->currentText();

   DeviceName = uii->DeviceNamLine->text();

   StopBits = uii->StopBitsBox->currentText();

   BaudRate = uii->BaudRateBox->currentText();

   Query.exec("insert into device ( DeviceName,BaudRate,StopBits,DataBits,Parity,FlowControl) values"
              "('"+DeviceName+"','"+BaudRate+"','"+StopBits+"','"+DataBits+"','"+Parity+"','"+FlowControl+"')");

this->hide();
data.close();
}



void AddDevice::on_Devices_clicked()
{

 qDebug()<<"Devices";
    if(data.isOpen()){
        qDebug()<<"true";
    }else{
        qDebug()<<"false";
    if (!data.open())
        qDebug()<< "false";
    }
    QSqlQuery query(QSqlDatabase::database("lala"));

    //query.exec(" select from rf (")

            QSqlQueryModel *model = new QSqlQueryModel;
               model->setQuery("select id, DeviceName, BaudRate, StopBits,DataBits,Parity,FlowControl from device",QSqlDatabase::database("lala"));

               model->setHeaderData(0, Qt::Horizontal, tr("id"));
               model->setHeaderData(1, Qt::Horizontal, tr("DeviceName"));
               model->setHeaderData(2, Qt::Horizontal, tr("BaudRate"));
               model->setHeaderData(3, Qt::Horizontal, tr("StopBits"));
               model->setHeaderData(4, Qt::Horizontal, tr("DataBits"));
               model->setHeaderData(5, Qt::Horizontal, tr("Parity"));
               model->setHeaderData(6, Qt::Horizontal, tr("FlowControl"));

                // model->setHeaderData(1, Qt::Horizontal, tr("LastName"));
               QTableView *viewer = new QTableView;
               qDebug()<<model;
               viewer->setModel(model);
            viewer->setMaximumSize(600,300);

            viewer->setGeometry(2,2,500,500);

               viewer->show();

}
