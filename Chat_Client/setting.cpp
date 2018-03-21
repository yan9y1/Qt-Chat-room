#include "setting.h"
#include "ui_setting.h"
#include "login.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <mainwindow.h>
#include <QMessageBox>

setting::setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
}

setting::~setting()
{
    delete ui;
}

void setting::on_nameButton_clicked()
{
    QString newName = ui->nameEdit->text();
    QString oldName = login::username;
    QSqlQuery changeName;
    changeName.prepare("UPDATE users SET name = :newname where name = :oldname");
    changeName.bindValue(":oldname",oldName);
    changeName.bindValue(":newname",newName);
    if(changeName.exec()){
        QMessageBox::information(this,"提示","修改成功");
        QSqlQuery changeOnline;
        changeOnline.prepare("UPDATE online SET name = :nnam where name = :onam");
        changeOnline.bindValue(":onam",oldName);
        changeOnline.bindValue(":nnam",newName);
        changeOnline.exec();
        login::username = newName;
        login::clientSocket->write("shuaxinnideshujukubiaoba123456");
    }
}

void setting::on_pwdButton_clicked()
{
    QString oldPwd = ui->oldPwdEdit->text();
    QString newPwd = ui->newPwdEdit->text();
    QString newPwdAgain = ui->newAgainEdit->text();
    if(newPwd != newPwdAgain){
        QMessageBox::warning(this,"警告","两次密码不一致");
    }else{
        QSqlQuery checkOldPwd;
        checkOldPwd.prepare("SELECT password from users where name = :name");
        checkOldPwd.bindValue(":name",login::username);
        checkOldPwd.exec();
        if(checkOldPwd.next()){
            QString trueOldPwd = checkOldPwd.value("password").toString();
            if(oldPwd != trueOldPwd){
                QMessageBox::warning(this,"警告","旧密码错误");
            }else{
                QSqlQuery changePwd;
                changePwd.prepare("UPDATE users SET password = :nPwd where name = :uNam");
                changePwd.bindValue(":nPwd",newPwd);
                changePwd.bindValue(":uNam",login::username);
                if(changePwd.exec()){
                    QMessageBox::information(this,"提示","成功修改密码");
                }
            }
        }
    }
}
