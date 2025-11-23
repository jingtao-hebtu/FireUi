/**************************************************************************

           Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FireEntry.cpp
   Author : tao.jing
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#include <QApplication>
#include "FuMainWid.h"
#include "AppMonitor.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    TF::AppMonitor::instance().initApp(argc, argv);

    TF::FuMainWid win;
    win.show();

    return QApplication::exec();
}