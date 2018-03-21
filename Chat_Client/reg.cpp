#include "reg.h"
#include "ui_reg.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "login.h"

reg::reg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reg)
{
    ui->setupUi(this);
}

reg::~reg()
{
    delete ui;
}

void reg::on_regButton_clicked()
{
    QString regID = ui->ID_edit->text();
    QString regpwd1 = ui->pwd_edit->text();
    QString regpwd2 = ui->pwd2_edit->text();
    if(regID == ""){
        QMessageBox::warning(this,tr("警告"),tr("用户名不能为空！"));
    }else if(regpwd1 == "" || regpwd2 == ""){
        QMessageBox::warning(this,tr("警告"),tr("密码不能为空！"));
    }else if(regpwd1 != regpwd2){
        QMessageBox::warning(this,tr("警告"),tr("两次密码不一致！"));
    }else{
        QSqlQuery reg_query;
        reg_query.prepare("SELECT * FROM users where name = ?");
        reg_query.addBindValue(regID);
        reg_query.exec();
        if(reg_query.next()){
            QMessageBox::warning(this,tr("警告"),tr("该用户名已存在！"));
        }else{
            QSqlQuery new_user;
            new_user.prepare("INSERT INTO users (name,password) VALUES (?,?)");
            new_user.addBindValue(regID);
            new_user.addBindValue(regpwd1);
            if(new_user.exec()){
                QMessageBox::information(this,tr("提示"),tr("注册成功！"));
            }else{
                QMessageBox::warning(this,tr("警告"),tr("注册失败！"));
            }
        }
    }
}
