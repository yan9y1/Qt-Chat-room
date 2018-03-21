#include "registerr.h"
#include "ui_register.h"

registerr::registerr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerr)
{
    ui->setupUi(this);
}

registerr::~registerr()
{
delete ui;
}
