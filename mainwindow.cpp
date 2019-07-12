#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(doSlot()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(cancel()));
}

void MainWindow::doSlot()
{
    if (ui->pushButton->text()=="Save file"){
        QFile file("D:/KM");
        if (file.size()!=0){
            file.remove();
        }
        c=0;
        if (!file.open(QIODevice::WriteOnly)){
            ui->pushButton->setText("Fail");
            c=1;
        }
        if (c==0){
        QDataStream out(&file);
        out<<r<<k;
        for (int j=0; j<r; j++){
            out<<ri[j].L;
            out<<ri[j].A;
            out<<ri[j].E;
            out<<ri[j].q;
            out<<ri[j].Sig;
        }
        for (int j=0; j<k; j++){
            out<<ki[j].F;
            out<<ki[j].sup;
        }
        if (out.status()==QDataStream::Ok){
            ui->pushButton->setText("Done");
        }
        else ui->pushButton->setText("Fail");
        }
        file.close();
        QFile file1("D:/KM.txt");
        if (!file1.open(QIODevice::WriteOnly)){
            ui->pushButton->setText("Fail");
        }
        for (int j=0; j<r; j++){
            QTextStream stream( &file1 );
            stream <<j+1<<" row, L="<<ri[j].L<<", A="<<ri[j].A<<", E="<<ri[j].E<<", q="<<ri[j].q<<", acceptable stress="<<ri[j].Sig<<"\r\n";
            if (stream.status()!=QTextStream::Ok){
                ui->pushButton->setText("Fail");
            }
        }
        for (int j=0; j<k; j++){
            QTextStream stream( &file1 );
            stream <<j+1<<" knot, F="<<ki[j].F<<", support";
            if(ki[j].sup==0){
                stream<<" doesn't exist.";
            }
            if(ki[j].sup==1){
                stream<<" does exist.";
            }
            stream<<"\r\n";
            if (stream.status()!=QTextStream::Ok){
                ui->pushButton->setText("Fail");
            }
        }
        file1.close();
    }
    if (ui->pushButton->text()=="Draw"){
        a=1;
        update();
        ui->pushButton->setText("Save file");
    }
    if (ui->pushButton->text().contains("Enter the support of the")){
        if (ui->lineEdit->text()=="0"||ui->lineEdit->text()=="1"){
            ki[i-1].sup=ui->lineEdit->text().toInt();
            if (i==k){
                ui->pushButton->setText("Draw");
                }
            if (i<k){
                i+=1;
                QString str2 = QString::number(i);
                str2=str1+str2+str3;
                ui->pushButton->setText(str2);
                }
        }
    }
    if (ui->pushButton->text().contains("Enter the force affecting the ")){
        double vall = ui->lineEdit->text().toDouble();
        if (vall!=0||ui->lineEdit->text()=="0"){
            ki[i-1].F=vall;
                    if (i==k){
                        str1="Enter the support of the ";
                        i=0;
                    }
                    if (i<k){
                        i+=1;
                        QString str2 = QString::number(i);
                        str2=str1+str2+str3;
                        ui->pushButton->setText(str2);
                    }
                }
            }
    if (ui->pushButton->text().contains("Enter the strain of the ")){
        double vall = ui->lineEdit->text().toDouble();
        if (vall!=0||ui->lineEdit->text()=="0"){
            ri[i-1].q=vall;
            if (i==r){
                str1="Enter the force affecting the ";
                str3=" knot";
                i=0;
            }
            if (i<r){
                i+=1;
                QString str2 = QString::number(i);
                str2=str1+str2+str3;
                ui->pushButton->setText(str2);
            }
        }
    }
    if (ui->pushButton->text().contains("Enter the acceptable stress of the ")){
        double vall = ui->lineEdit->text().toDouble();
        if (vall>0){
            ri[i-1].Sig=vall;
            if (i==r){
                str1="Enter the strain of the ";
                i=0;
            }
            if (i<r){
                i+=1;
                QString str2 = QString::number(i);
                str2=str1+str2+str3;
                ui->pushButton->setText(str2);
            }
        }
    }
    if (ui->pushButton->text().contains("Enter the elastic moment of the ")){
        double vall = ui->lineEdit->text().toDouble();
        if (vall>0){
            ri[i-1].E=vall;
            if (i==r){
                str1="Enter the acceptable stress of the ";
                i=0;
            }
            if (i<r){
                i+=1;
                QString str2 = QString::number(i);
                str2=str1+str2+str3;
                ui->pushButton->setText(str2);
            }
        }
    }
    if (ui->pushButton->text().contains("Enter the cross-sectional area of the ")){
        double vall = ui->lineEdit->text().toDouble();
        if (vall>0){
            ri[i-1].A=vall;
            if (i==r){
                str1="Enter the elastic moment of the ";
                i=0;
            }
            if (i<r){
                i+=1;
                QString str2 = QString::number(i);
                str2=str1+str2+str3;
                ui->pushButton->setText(str2);
            }
        }
    }
    if (ui->pushButton->text().contains("Enter the length the ")){
        double vall = ui->lineEdit->text().toDouble();
            if (vall>0){
                    ri[i-1].L=vall;
                    ki[i].x=ki[i-1].x+vall;
                    ki[i].y=100;
                        if (i==r){
                            str1="Enter the cross-sectional area of the ";
                            i=0;
                        }
                        if (i<r){
                            i+=1;
                            QString str2 = QString::number(i);
                            str2=str1+str2+str3;
                            ui->pushButton->setText(str2);
                        }
                    }
                    }

    if (ui->pushButton->text()=="Enter the number of rows"){
        int vall = ui->lineEdit->text().toInt();
        if (vall>0){
            r=vall;
            k=r+1;
            createRows(r);
            createKnots(k);
            str1="Enter the length the ";
            str3=" row";
            i=1;
            QString str2 = QString::number(i);
            str2=str1+str2+str3;
            ui->pushButton->setText(str2);
        }
    }
}

void MainWindow::cancel(){
    a=0;
    update();
    delete[]ri;
    delete[]ki;
    ui->pushButton->setText("Enter the number of rows");
}

void MainWindow::createRows(int r){

    ri=new Row<double> [r];

}

void MainWindow::createKnots(int k){

    ki=new Knot<double> [k];
    ki[0].x=0;
    ki[0].y=100;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    QRect r1(QPoint(20, 20), QSize(400, 200));
    painter.drawRect(r1);
    if (a==1){
        QPainter painter(this);
        b=300/ki[k-1].x;
        for (int i=0; i<k; i++){
            ki[i].x=ki[i].x*b+50;
        }
        for (int i=0; i<r; i++){
            painter.setPen(Qt::black);
            int x1=ki[i].x;
            int x2=ki[i+1].x;
            int x3=100;
            int x4=100;
            QLine l1(x1,x3,x2,x4);
            painter.drawLine(l1);
            int y1=(x2-x1)/2;
            QString stra=QString::number(i+1);
            painter.drawText(x1+y1,x3+10,stra);
            if (ri[i].q!=0){
                painter.setPen(Qt::green);
                painter.setBrush(Qt::green);
                    if (ri[i].q>0){
                            for (int inx=x1; inx<x2; inx+=15){
                                QPointF points[3] = {
                                    QPointF(inx, x3),
                                    QPointF(inx-10, x3+5),
                                    QPointF(inx-10, x3-5),
                                };
                                painter.drawPolygon(points, 3);
                            }
                        }
                    if (ri[i].q<0){
                            for (int inx=x1; inx<x2; inx+=15){
                                QPointF points[3] = {
                                    QPointF(inx, x3),
                                    QPointF(inx+10, x3-5),
                                    QPointF(inx+10, x3+5),
                                };
                                painter.drawPolygon(points, 3);
                            }
                        }
                }
            }
        for (int i=0; i<k; i++){
            painter.setPen(Qt::red);
            painter.setBrush(Qt::red);
            painter.drawPoint(ki[i].x, ki[i].y);
            painter.setPen(Qt::blue);
            painter.setBrush(Qt::blue);
            if (ki[i].F!=0){
                if (ki[i].F>0){
                    int x1=ki[i].x;
                    int x2=ki[i].y;
                    int x3=x1+15;
                    QLine l1(x1,x2,x3,x2);
                    painter.drawLine(l1);
                    QPointF points[4] = {
                        QPointF(x3, x2),
                        QPointF(x3, x2+5),
                        QPointF(x3+10, x2),
                        QPointF(x3, x2-5)
                    };
                    painter.drawPolygon(points, 4);
                }
                if (ki[i].F<0){
                    int x1=ki[i].x;
                    int x2=ki[i].y;
                    int x3=x1-15;
                    QLine l1(x1,x2,x3,x2);
                    painter.drawLine(l1);
                    QPointF points[4] = {
                        QPointF(x3, x2),
                        QPointF(x3, x2+5),
                        QPointF(x3-10, x2),
                        QPointF(x3, x2-5)
                    };
                    painter.drawPolygon(points, 4);
                }
            }
            if (ki[i].sup==1){
                painter.setPen(Qt::black);
                int x1=ki[i].x;
                int x2=ki[i].y;
                QLine l1 (x1,x2,x1,x2+10);
                painter.drawLine(l1);
                QLine l2(x1-10,x2+10,x1+10,x2+10);
                painter.drawLine(l2);
                for (int x=x1-10; x<x1+10; x+=4){
                    QLine l3(x,x2+10,x-5,x2+20);
                    painter.drawLine(l3);
                }
            }
        }
}
}

MainWindow::~MainWindow()
{
    delete ui;
}
