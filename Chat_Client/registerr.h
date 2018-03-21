#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>

namespace Ui {
class registerr;
}

class registerr : public QDialog
{
    Q_OBJECT

public:
    explicit registerr(QWidget *parent = 0);
    ~registerr();

private:
    Ui::registerr *ui;
};



#endif // REGISTER_H
