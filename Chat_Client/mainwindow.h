#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void DB_Connect();
    void showID();
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void closeEvent(QCloseEvent *event);
public slots:
    void receiveMes();
private slots:
    void on_sendButton_clicked();
    void on_shezhiButton_clicked();
};

#endif // MAINWINDOW_H
