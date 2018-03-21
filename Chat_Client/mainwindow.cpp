#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <login.h>
#include <QSqlQuery>
#include <setting.h>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showID(){
    ui->lineEdit_2->setStyleSheet("background:rgb(240, 240, 240);border-width:0;border-style:outset");
    QString uName = login::username;
    ui->lineEdit_2->setText("当前昵称：" + uName);
    connect(login::clientSocket,SIGNAL(readyRead()),this,SLOT(receiveMes()));
}

void MainWindow::receiveMes(){
    QByteArray others = login::clientSocket->readAll();
    QString othersStr = QVariant(others).toString();
    QString cutstr1 = othersStr;
    QString cutstr2 = othersStr;
    int pos = cutstr1.indexOf(":");
    QString recName = cutstr1.remove(pos,othersStr.length() - pos);
    if(recName == login::username){
        QString ziji = cutstr2.remove(0,pos + 2);
        //QString show = ziji + ": " + login::username;
        ui->roomEdit->setTextColor(QColor("blue"));
        ui->roomEdit->append(ziji);
        ui->roomEdit->setAlignment(Qt::AlignRight);
        ui->roomEdit->setTextColor(QColor("black"));
    }else{
        ui->roomEdit->append(othersStr);
        ui->roomEdit->setAlignment(Qt::AlignLeft);
    }
}

void MainWindow::on_sendButton_clicked()
{
    QString messages = login::username + ": " + ui->sendEdit->text();
    login::clientSocket->write(messages.toStdString().c_str(),strlen(messages.toStdString().c_str()));
    ui->sendEdit->clear();
    QString uName = login::username;
    ui->lineEdit_2->setText("当前昵称：" + uName);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    QSqlQuery delete_from_online;
    delete_from_online.prepare("DELETE FROM online where name = ?");
    QString uName = login::username;
    delete_from_online.addBindValue(uName);
    delete_from_online.exec();
    login::clientSocket->write("shuaxinnideshujukubiaoba123456");
    login::clientSocket->waitForBytesWritten(20000);
    login::clientSocket->disconnectFromHost();
    login::clientSocket->close();
}


void MainWindow::on_shezhiButton_clicked()
{
    setting set;
    set.show();
    set.exec();
}
