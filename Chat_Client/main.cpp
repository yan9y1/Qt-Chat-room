#include "mainwindow.h"
#include <QApplication>
#include "login.h"
#include "registerr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    login loginW;
    loginW.show();
    if(loginW.exec() == QDialog::Accepted){
        w.setWindowFlags(w.windowFlags()&~Qt::WindowMinMaxButtonsHint|Qt::WindowMinimizeButtonHint);
        w.show();
        w.showID();
        return a.exec();
    }
    else{
        return 0;
    }
}
