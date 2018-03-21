#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <login.h>

namespace Ui {
class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();

private slots:
    void on_nameButton_clicked();

    void on_pwdButton_clicked();

private:
    Ui::setting *ui;
};

#endif // SETTING_H
