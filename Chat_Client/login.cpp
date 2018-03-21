#include "login.h"
#include "ui_login.h"
#include "reg.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

QSqlDatabase login::db = QSqlDatabase();
QString login::username = QString();
QTcpSocket* login::clientSocket = new QTcpSocket();

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //连接数据库
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("chatroom");
    db.setUserName("root");
    db.setPassword("541536638yy.");
    bool ok = db.open();
    if(ok){
        qDebug()<<"成功连接数据库";
    }else{
        QMessageBox::warning(this,"警告","无法连接数据库");
    }
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_2_clicked()
{
    reg regWindow;
    regWindow.show();
    regWindow.exec();
}

void login::on_loginButton_clicked()
{
    //从登录对话框中获取用户名和密码
    username = ui->ID->text();
    QString password = ui->pwd->text();
    //账号密码验证
    QSqlQuery check_user;
    check_user.prepare("SELECT * FROM users where name = ?");
    check_user.addBindValue(username);
    check_user.exec();
    if(check_user.next()){
        QString pswd = check_user.value("password").toString();
        if(pswd == password){
            //一旦登陆成功，与服务器建立连接
            clientSocket->abort();
            clientSocket->connectToHost("127.0.0.1",9998);
            //一旦登陆成功，则将该用户插入online表
            QSqlQuery insertIntoOnline;
            insertIntoOnline.prepare("INSERT INTO online(name) VALUES(?)");
            insertIntoOnline.addBindValue(username);
            insertIntoOnline.exec();
            //一旦登陆成功，则向服务器发送刷新在线列表的信号
            clientSocket->write("shuaxinnideshujukubiaoba123456");
            //一旦登陆成功，则关闭登陆对话框，打开mainwindow对话框
            accept();

        }else{
            QMessageBox::warning(this,tr("警告"),tr("密码错误！"));
        }
    }else{
        QMessageBox::warning(this,tr("警告"),tr("该用户名不存在！"));
    }
}

