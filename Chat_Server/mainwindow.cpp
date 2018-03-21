#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    serverListen();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("chatroom");
    db.setUserName("root");
    db.setPassword("***********");
    bool ok = db.open();
    if(!ok){
        QMessageBox::warning(this,"警告","无法连接数据库");
    }
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serverListen(){
    tcpServer = new QTcpServer();
    tcpServer->listen(QHostAddress::Any,9998);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnect()));
}

void MainWindow::newConnect(){
    QTcpSocket* newSocket = tcpServer->nextPendingConnection();
    socket_list.append(newSocket);
    connect(newSocket,SIGNAL(readyRead()),this,SLOT(chat()));
}

void MainWindow::chat(){
    qDebug()<<"shoudao";
    for(int i = 0 ; i < socket_list.size(); i++){
        QTcpSocket* sock = socket_list.at(i);
        if(sock->isReadable()){
            QByteArray content = sock->readAll();
            QString contentStr = QVariant(content).toString();
            if(contentStr == "shuaxinnideshujukubiaoba123456"){
                qDebug()<<"jinlaile";
                QSqlQuery onlineList;
                onlineList.prepare("SELECT * FROM online");
                onlineList.exec();
                ui->onlineList->clear();
                while(onlineList.next()){
                    QString ID = onlineList.value("name").toString();
                    ui->onlineList->append(ID);
                }
            }else{ //否则向每个客户端都发回这个消息
                if(contentStr != ""){
                    ui->chatRoom->append(contentStr);
                }
                for(int j = 0; j < socket_list.size(); j++){
                    QTcpSocket* sendBack = socket_list.at(j);
                    sendBack->write(content);
                }
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString guangbo = "管理员: " + ui->sendEdit->text();
    ui ->chatRoom->append(guangbo);
    ui->sendEdit->clear();
    for(int j = 0; j < socket_list.size(); j++){
        QTcpSocket* sendBack = socket_list.at(j);
        sendBack->write(guangbo.toStdString().c_str(),strlen(guangbo.toStdString().c_str()));
    }
}
