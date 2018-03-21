#ifndef REG_H
#define REG_H

#include <QDialog>
#include <login.h>
#include <QSqlDatabase>

namespace Ui {
class reg;
}

class reg : public QDialog
{
    Q_OBJECT

public:
    explicit reg(QWidget *parent = 0);
    QSqlDatabase db = login::db;
    ~reg();

private slots:
    void on_regButton_clicked();

private:
    Ui::reg *ui;
};

#endif // REG_H
