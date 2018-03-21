#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpServer* tcpServer;
    QList<QTcpSocket*> socket_list;
    void serverListen();
    QSqlDatabase db;

private:
    Ui::MainWindow *ui;
    QString userName;

public slots:
    void newConnect();
    void chat();
private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
