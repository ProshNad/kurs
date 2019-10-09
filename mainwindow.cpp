#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <QApplication>
#include <QDesktopWidget>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QTreeView>
#include  <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QFileInfo>
#include <QMessageBox>
#include <QColor>
#include <QFileDialog>
#include <QByteArray>
#include <QProcess>
#include <QRegExp>
#include <QProgressDialog>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include "symbolicc++.h"
#include "multinomial.h"

#include <fstream>
using namespace std;
bool reg=0;
int reg2=0;
 int g;//=ui->treeWidget->topLevelItemCount();
int numgr=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom,true);
    ui->plot->xAxis->setLabel("X");
    ui->plot->yAxis->setLabel("Y");
   // ui->frame_3->setVisible(0);
   // ui->plot->addAction(ui->aang);
    ui->plot->addAction(ui->atat);
    ui->plot->addAction(ui->astan);

    ui->frame_4->addAction(ui->achan);
    ui->frame_3->addAction(ui->asave);

    ui->frame_2->setVisible(0);
    ui->frame_3->setVisible(0);
    ui->frame_4->setVisible(0);

    connect(ui->plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));

   // memory
    QFile fileIn("mem.txt");

    if (fileIn.open(QIODevice::ReadOnly))
    {
        QDataStream in(&fileIn);
        in.setVersion(QDataStream::Qt_4_6);

        in >> memory;

        fileIn.close();
    }


    ui->treeWidget->clear();
    QString s,s1;





    foreach (s, memory.uniqueKeys()) {
     qDebug()<<memory.values(s);
      QTreeWidgetItem *item = new QTreeWidgetItem();
      item->setText(0, s);

      foreach (s1,memory.values(s) ) {
          QTreeWidgetItem *child = new QTreeWidgetItem();
          child->setText(0, s1);

          item->addChild(child);
      }
      ui->treeWidget->addTopLevelItem(item);



    }



 QStringList strArray;
 QFile filesi("m1.txt");
 filesi.open(QIODevice::ReadOnly);
 QTextStream stream(&filesi);
 while(!stream.atEnd())
 {
     strArray.append(stream.readLine());
 }
 filesi.close();

 g=strArray[0].toInt();




}

MainWindow::~MainWindow()
{

    QFile fileOut("mem.txt");
    if (fileOut.open(QIODevice::WriteOnly))
    {
        QDataStream out(&fileOut);
        out.setVersion(QDataStream::Qt_4_6);

        out << memory;
       // fileOut.flush();
        fileOut.close();
    }



     QFile file22("m1.txt");
file22.open(QIODevice::ReadWrite | QIODevice::Truncate);
QTextStream t22(&file22);


  t22 <<g;
file22.close();


    delete ui;
}

void MainWindow::mouseMove(QMouseEvent *mouseEvent)
{


    QToolTip::showText(mouseEvent->globalPos(),
                       "xAxis=" + QString::number(ui->plot->xAxis->pixelToCoord(mouseEvent->pos().x()), 'f', 2) + "\n" +
                       "yAxis=" + QString::number(ui->plot->yAxis->pixelToCoord(mouseEvent->pos().y()), 'f', 2) + "\n" ,
                       this, rect());
    if(reg2==1){
       QString name1=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().row())+ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().parent().row())+"1.txt";
       double kofx=ui->plot->xAxis->pixelToCoord(mouseEvent->pos().x());
       double kofy=ui->plot->yAxis->pixelToCoord(mouseEvent->pos().y());

       QFile file1(name1);
       file1.open(QIODevice::ReadOnly);
       QStringList datList;
      while (!file1.atEnd()) {
       QString line = file1.readLine();
       datList.append(line.split(' ',QString::SkipEmptyParts));
      }
       file1.close();

        int j=0;
        if(!datList.isEmpty()){

        QVector<double> xx(datList.size()/2), yy(datList.size()/2);
        for(int i=0;i<datList.size()/2;i++){
            xx[i]=datList.at(j).toDouble()+kofx;
            yy[i]=datList.at(j+1).toDouble()+kofy;
            j=j+2;
        }
        if(!reg){numgr=0;}

         ui->plot->replot();
        ui->plot->addGraph(ui->plot->xAxis, ui->plot->yAxis);


        ui->plot->graph(numgr)->setData(xx, yy);


        ui->plot->replot();

        numgr++;

        j=0;

        for(int i=0;i<datList.size()/2;i++){
            xx[i]=datList.at(j).toDouble()+kofx;
            yy[i]=datList.at(j+1).toDouble()*(-1)+kofy;
            j=j+2;
        }

        ui->plot->addGraph(ui->plot->xAxis, ui->plot->yAxis);

        ui->plot->graph(numgr)->setData(xx, yy);

        ui->plot->replot();
         numgr++;


    }
    }


}

void MainWindow::on_pushButton_clicked()
{

    double dia;
    int toch;
    toch=ui->toch->value();
    dia=abs((ui->diap1->value())-(ui->diap2->value()));

    QString str=ui->textEdit->toPlainText();
    QStringList strList=str.split('\n');
    str=strList.at(0);

    str.replace("^2","**2");


    QString cstr=str;
    QString nstr="0";

    if(str.indexOf('=')!=-1){
    nstr= cstr.remove(0,cstr.indexOf('=')+1);
    str.truncate(str.indexOf('='));}

qDebug()<<str;
qDebug()<<nstr;

QFile file0("in.txt");
file0.open(QIODevice::ReadWrite | QIODevice::Truncate);
QTextStream t0(&file0);

t0<<str<<endl<<nstr;
file0.close();

 QProcess *process = new QProcess(this);
  process->execute("python si.py");


/*
QStringList strArray;
QFile filesi("simp.cpp");
filesi.open(QIODevice::ReadOnly);
QTextStream stream(&filesi);
while(!stream.atEnd())
{
    strArray.append(stream.readLine());
}
filesi.close();




strArray[10]="Symbolic f="+str+";";
strArray[11]="Symbolic f1="+nstr+";";
strArray[40]="double zx="+QString::number(ui->diap1->value())+";";
strArray[42]="for(int i=0;i<"+QString::number(toch)+"+1;i++){";
strArray[53]="zx=zx+"+QString::number(dia/toch)+";";

//double zx=-50;//40
//for(int i=0;i<100;i++){//42
//zx=zx+1;//53


QFile fileis("simp.cpp");
fileis.open(QIODevice::WriteOnly);
QTextStream stream2(&fileis);
    foreach(QString s, strArray)
    {
        stream2<<s<<endl;
    }
    fileis.close();

    QProcess *process = new QProcess(this);
    QMessageBox::about(this, "Преобразование уравнения","Сейчас будет проводиться преобразование уравнения, это займет некоторое время. Пожалуйста,не паникуйте и ничего не трогайте!!!");
    process->execute("g++ -o simp simp.cpp");
    QMessageBox::about(this, "Преобразование уравнения","Все еще проводиться преобразование уравнения, это займет совсем немного времени, потому что основная работа уже выполнена. Пожалуйста,не паникуйте и ничего не трогайте!!!");
    process->execute("simp.exe");

  /*
        process->execute("python si.py");
*/





qDebug()<<"ok";

 /*QFile file("forsimp.txt");//файл с упрощенным выражением// поменять на simpli.txt
 file.open(QIODevice::ReadOnly);
 QTextStream t(&file);
 QString data;
 data=t.readAll();
 data=data+"=0";
 ui->textEdit->clear();
 ui->textEdit->setText(data);
 file.close();*/

QStringList strArray;
QFile file("simpli.txt");//файл с упрощенным выражением
 file.open(QIODevice::ReadOnly);
 QTextStream t(&file);
 QString data;

while(!t.atEnd())
{
    strArray.append(t.readLine());
}
file.close();

 data=strArray[0]+"=0";
 data.replace("**2","^2");

 ui->textEdit->clear();
 ui->textEdit->setText(data);




 //вот тут остановились

 double a,b,c,d,e,f0;
 a=strArray[1].toDouble();
 b=strArray[3].toDouble()/2;
 c=strArray[2].toDouble();
 d=strArray[4].toDouble()/2;
 e=strArray[5].toDouble()/2;
 f0=strArray[6].toDouble();

 QFile file11("eq.txt");
file11.open(QIODevice::ReadWrite | QIODevice::Truncate);
QTextStream t11(&file11);
t11<<a+c<<endl//A+C
  <<a*c-b*b<<endl//a*c-b*b
 <<a*c*f0+b*e*d+b*e*d-d*d*c-e*e*a-b*b*f0 <<endl;
file11.close();




 QFile file1("eq.txt");//файл с инвариантами
  QStringList strArray1;
 file1.open(QIODevice::ReadOnly);
 QTextStream t1(&file1);
 while(!t1.atEnd())
 {
     strArray1.append(t1.readLine());
 }
 file1.close();

 qDebug()<<strArray1;
 ui->lS->setText(strArray1.at(0));
 ui->lO->setText(strArray1.at(1));
 ui->lQ->setText(strArray1.at(2));


//сделать точки тут

 Symbolic x("x"),y("y");
Symbolic f1=x*x;
Symbolic f2=y*y;
Symbolic f3=y*x;
Symbolic f4=x;
Symbolic f5=y;
Symbolic f6=1;
 //Ax^2+2Bxy+Cy^2+2Dx+2Ey+F=0f
Symbolic f=f1*a+f2*c+f3*b+f4*d+f5*e+f6*f0;

double a1,b1,c1,y1;
double zx=ui->diap1->value();

 QFile file22("graf.txt");
file22.open(QIODevice::ReadWrite | QIODevice::Truncate);
QTextStream t22(&file22);

for(int i=0;i<toch+1;i++){
 Symbolic w=f[x==zx];
 a1=w.coeff(y,2);
 b1=w.coeff(y,1);
 c1=w.coeff(y,0);

 y1 = ( -1*b1 + sqrt(b1*b1 - 4*a1*c1) ) / (2 * a1);
  t22 << zx<<" "<< y1 << endl;

zx=zx+dia/toch;
}
file22.close();






 QFile file2("graf.txt");//файл с точками
 file2.open(QIODevice::ReadOnly);

 QStringList datList;
while (!file2.atEnd()) {
 QString line = file2.readLine();
 datList.append(line.split(' ',QString::SkipEmptyParts));
}
 file2.close();
  qDebug() << datList;
  int j=0;

  QVector<double> xx(toch+1), yy(toch+1);//200!!!
  for(int i=0;i<toch+1;i++){//200!!!
      xx[i]=datList.at(j).toDouble();
      yy[i]=datList.at(j+1).toDouble();
      j=j+2;
  }

  int n=0;
   ui->plot->replot();
  ui->plot->addGraph(ui->plot->xAxis, ui->plot->yAxis);
  ui->plot->graph(n)->setPen(QColorDialog::getColor(Qt::magenta, this,QString::fromUtf8("Выберите цвет графика")));
 // ui->plot->graph(n)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
  ui->plot->graph(n)->setData(xx, yy);

 // ui->plot->graph(n)->setSelectable(QCP::stWhole);
  ui->plot->replot();
  n++;

  j=0;
  for(int i=0;i<toch+1;i++){//200!!!
      xx[i]=datList.at(j).toDouble();
      yy[i]=datList.at(j+1).toDouble()*(-1);
      j=j+2;
  }

  ui->plot->addGraph(ui->plot->xAxis, ui->plot->yAxis);
  ui->plot->graph(n)->setPen(QColorDialog::getColor(Qt::magenta, this,QString::fromUtf8("Выберите цвет графика")));
 // ui->plot->graph(n)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
  ui->plot->graph(n)->setData(xx, yy);

  ui->plot->replot();
  ui->frame_2->setVisible(1);

}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{


     int m=ui->treeWidget->currentIndex().row();
     int k=ui->treeWidget->currentIndex().parent().row();
     qDebug()<<"pressed :"<<k<<" "<<m;

    if(!(item->childCount())){//нажали на какой-то график
       if(!reg){//reg=1->множественное отображение
        ui->plot->clearGraphs();
        ui->plot->replot();}

        ui->lS->setText("");
        ui->lO->setText("");
        ui->lQ->setText("");
        ui->frame_2->setVisible(1);//
        ui->frame_3->setVisible(1);//
        ui->frame_4->setVisible(1);//
        ui->label_18->setText("");

       QString name1=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().row())+ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().parent().row())+"1.txt";
       QString name2=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().row())+ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().parent().row())+"2.txt";
       QString name3=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().row())+ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().parent().row())+"3.txt";
       name1.replace("|","-"); name2.replace("|","-"); name3.replace("|","-");
       //рисуем график
       QFile file1(name1);
       file1.open(QIODevice::ReadOnly);
       QStringList datList;
      while (!file1.atEnd()) {
       QString line = file1.readLine();
       datList.append(line.split(' ',QString::SkipEmptyParts));
      }
       file1.close();
        qDebug() << datList;
        int j=0;
        if(!datList.isEmpty()){

        QVector<double> xx(datList.size()/2), yy(datList.size()/2);
        for(int i=0;i<datList.size()/2;i++){
            xx[i]=datList.at(j).toDouble();
            yy[i]=datList.at(j+1).toDouble();
            j=j+2;
        }
        if(!reg){numgr=0;}

         ui->plot->replot();
        ui->plot->addGraph(ui->plot->xAxis, ui->plot->yAxis);
        QColor col=QColorDialog::getColor(Qt::magenta, this,QString::fromUtf8("Выберите цвет графика"));
        ui->plot->graph(numgr)->setPen(col);

        ui->plot->graph(numgr)->setData(xx, yy);


        ui->plot->replot();

        numgr++;

        j=0;

        for(int i=0;i<datList.size()/2;i++){
            xx[i]=datList.at(j).toDouble();
            yy[i]=datList.at(j+1).toDouble()*(-1);
            j=j+2;
        }

        ui->plot->addGraph(ui->plot->xAxis, ui->plot->yAxis);
       // ui->plot->graph(numgr)->setPen(QColorDialog::getColor(Qt::magenta, this,QString::fromUtf8("Выберите цвет графика")));
        ui->plot->graph(numgr)->setPen(col);
        ui->plot->graph(numgr)->setData(xx, yy);

        ui->plot->replot();
         numgr++;


       //нарисовали график

        //читаем инварианты
        QFile file2(name2);
        file2.open(QIODevice::ReadOnly);
        QStringList strArray1;

       QTextStream t1(&file2);
       while(!t1.atEnd())
       {
           strArray1.append(t1.readLine());
       }
       file2.close();

       qDebug()<<strArray1;
       ui->lS->setText(strArray1.at(0));
       ui->lO->setText(strArray1.at(1));
       ui->lQ->setText(strArray1.at(2));
       //вывели инварианты
       //читаем уравнение
       QFile file3(name3);
       file3.open(QIODevice::ReadOnly);
       QStringList strArray;


        QTextStream t(&file3);
        QString data;

       while(!t.atEnd())
       {
           strArray.append(t.readLine());
       }
       file3.close();

        data=strArray[0]+"=0";
        data.replace("**2","^2");
        ui->label_18->setText(data);




}

    }
    else{
        ui->frame_2->setVisible(0);
        ui->frame_3->setVisible(0);
        ui->frame_4->setVisible(0);


    }

}

void MainWindow::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{

    QTreeWidgetItem *item=ui->treeWidget->itemAt(pos);

    if(!item){
        QMenu menu1(tr("Context menu"),this);
        menu1.addAction(ui->aris);
        menu1.addAction(ui->aris2);
        menu1.addAction(ui->anewch);
        menu1.exec(ui->treeWidget->viewport()->mapToGlobal(pos));
    }
    else{
        if(item->childCount()){
            QMenu menu2(tr("Context menu"),this);
            menu2.addAction(ui->adel);
            menu2.addAction(ui->aneweel);
            menu2.exec(ui->treeWidget->viewport()->mapToGlobal(pos));

        }
        else{
            QMenu menu3(tr("Context menu"),this);
            menu3.addAction(ui->adel);
            menu3.exec(ui->treeWidget->viewport()->mapToGlobal(pos));
        }

    }

}

void MainWindow::on_treeWidget_itemPressed(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_anewch_triggered()
{
    /* int m=ui->treeWidget->currentIndex().row();
     int k=ui->treeWidget->currentIndex().parent().row();
     qDebug()<<"pressed :"<<k<<" "<<m;
*/

    QTreeWidgetItem *item = new QTreeWidgetItem();
    bool ok;


    QString p=QString::number(g)+"|"+QInputDialog::getText(this,
                                    QString::fromUtf8("Введите название нового чертежа"),
                                    QString::fromUtf8("Имя:"),
                                    QLineEdit::Normal,
                                    "Чертеж", &ok);

    item->setText(0, p);
    QTreeWidgetItem *child = new QTreeWidgetItem();
    QString c=QInputDialog::getText(this,
                                    QString::fromUtf8("Введите название нового элемента"),
                                    QString::fromUtf8("Имя:"),
                                    QLineEdit::Normal,
                                    "Элемент", &ok);
    child->setText(0,c);
    item->addChild(child);
    ui->treeWidget->addTopLevelItem(item);
    memory.insert(p,c);
    g++;
}

void MainWindow::on_adel_triggered()
{






    QString c=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().column());
    if(ui->treeWidget->currentItem()->parent()){
        QString name1=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().row())+ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().parent().row())+"1.txt";
        QString name2=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().row())+ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().parent().row())+"2.txt";
        QString name3=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().row())+ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().parent().row())+"3.txt";
        name1.replace("|","-"); name2.replace("|","-"); name3.replace("|","-");
           //точки
           QFile file1(name1);
           file1.open(QIODevice::WriteOnly);
           file1.close();
           file1.remove();

           //инварианты
           QFile file2(name2);
           file2.open(QIODevice::ReadWrite | QIODevice::Truncate);
           file2.close();
           file2.remove();

           //уравнение
           QFile file3(name3);
           file3.open(QIODevice::ReadWrite | QIODevice::Truncate);
           file3.close();
           file3.remove();
           QFile::copy("simpli.txt",name3);
           QStringList strArray;

           QFile file(name3);//файл с упрощенным выражением
            file.open(QIODevice::ReadOnly);
            QTextStream t(&file);
            QString data;


    QString p=ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().column());
    qDebug()<<"Element:"<<c<<"Perent:"<<p;
    memory.remove(p,c);
    //удалить файл тут








    }
    else{




        QString s1;
        foreach (s1,memory.values(c)) {
           memory.remove(c,s1);
        }
        QDir recoredDir("D:/QT/Qt5.3.2/Tools/QtCreator/bin/build-prob-Desktop_Qt_5_3_MinGW_32bit-Debug");
        QStringList allFiles = recoredDir.entryList(QDir::Files,QDir::NoSort);
        QStringList needf;
        qDebug()<<allFiles;
        for(int i=0;i<allFiles.size();i++){
            if(allFiles[i].indexOf(c.replace("|","-"))!=-1){
                needf.push_back(allFiles[i]);
            }
        }
        qDebug()<<needf;

        for(int i=0; i<needf.size();i++){
            QFile file1(needf[i]);
            file1.remove();
        }

    }


    ui->treeWidget->clear();
    QString s,s1;




    foreach (s, memory.uniqueKeys()) {
     qDebug()<<memory.values(s);
      QTreeWidgetItem *item = new QTreeWidgetItem();
      item->setText(0, s);

      foreach (s1,memory.values(s) ) {
          QTreeWidgetItem *child = new QTreeWidgetItem();
          child->setText(0, s1);

          item->addChild(child);
      }
      ui->treeWidget->addTopLevelItem(item);
    }

}

void MainWindow::on_aneweel_triggered()
{
     bool ok;
    QTreeWidgetItem *child = new QTreeWidgetItem();
    QString c=QInputDialog::getText(this,
                                    QString::fromUtf8("Введите название нового элемента"),
                                    QString::fromUtf8("Имя:"),
                                    QLineEdit::Normal,
                                    "Элемент", &ok);
    child->setText(0, c);
    memory.insert(ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().column()),c);
    ui->treeWidget->currentItem()->addChild(child);
}

void MainWindow::on_aris_triggered()
{
    reg=1;
    QMessageBox::about(this, "Переключение режима!","Включен режим множестенного отображения.");
    ui->treeWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    reg2=0;

}

void MainWindow::on_aris2_triggered()
{
    reg=0;
    QMessageBox::about(this, "Переключение режима!","Включен режим индивидуального отображения.");
     ui->treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);

QList<QTreeWidgetItem *> itemList;
itemList = ui->treeWidget->selectedItems();
foreach(QTreeWidgetItem *item, itemList)
{
   //QString str = item->text();
   //str is what you want
    item->setSelected(0);
}

ui->plot->clearGraphs();
ui->plot->replot();


}

void MainWindow::on_label_17_linkActivated(const QString &link)
{

}

void MainWindow::on_frame_4_customContextMenuRequested(const QPoint &pos)
{

}

void MainWindow::on_achan_triggered()
{
    ui->frame_4->setVisible(0);
    ui->frame_2->setVisible(0);
}

void MainWindow::on_asave_triggered()
{
    ui->frame_4->setVisible(1);
    ui->frame_2->setVisible(1);
    /* int m=ui->treeWidget->currentIndex().row();
     int k=ui->treeWidget->currentIndex().parent().row();
     qDebug()<<"pressed :"<<k<<" "<<m;
*/
 QString name1=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().row())+ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().parent().row())+"1.txt";
 QString name2=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().row())+ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().parent().row())+"2.txt";
 QString name3=ui->treeWidget->currentItem()->text(ui->treeWidget->currentIndex().row())+ui->treeWidget->currentItem()->parent()->text(ui->treeWidget->currentIndex().parent().row())+"3.txt";
 name1.replace("|","-"); name2.replace("|","-"); name3.replace("|","-");
    //точки
    QFile file1(name1);
    file1.open(QIODevice::WriteOnly);
    file1.close();

    file1.remove();
    QFile::copy("graf.txt",name1);
    //инварианты
    QFile file2(name2);
    file2.open(QIODevice::ReadWrite | QIODevice::Truncate);
    file2.close();
    file2.remove();
    QFile::copy("eq.txt",name2);
    //уравнение
    QFile file3(name3);
    file3.open(QIODevice::ReadWrite | QIODevice::Truncate);
    file3.close();
    file3.remove();
    QFile::copy("simpli.txt",name3);
    QStringList strArray;

    QFile file(name3);//файл с упрощенным выражением
     file.open(QIODevice::ReadOnly);
     QTextStream t(&file);
     QString data;

    while(!t.atEnd())
    {
        strArray.append(t.readLine());
    }
    file.close();

     data=strArray[0]+"=0";
     data.replace("**2","^2");
     ui->label_18->setText(data);




}

void MainWindow::on_atat_triggered()
{
   if(!reg){
        reg2=1;
        QMessageBox::about(this, "Переключение режима!","Включен режим перетаскивания");

   }

   else{
       QMessageBox::about(this, "Переключение режима!","Переключение режима невозможно при режиме множественного отображения");
   }



}

void MainWindow::on_astan_triggered()
{
    if(!reg){
     reg2=0;
     QMessageBox::about(this, "Переключение режима!","Включен стандартный режим");}
    else{
        QMessageBox::about(this, "Переключение режима!","Переключение режима невозможно при режиме множественного отображения");
    }
}


