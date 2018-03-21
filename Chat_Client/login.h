#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlDatabase>
#include <QTcpSocket>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    static QSqlDatabase db;
    static QString username;
    static QTcpSocket* clientSocket;
    ~login();

private slots:
    void on_pushButton_2_clicked();
    void on_loginButton_clicked();

private:
    Ui::login *ui;

};

#endif // LOGIN_H
