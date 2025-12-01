/**************************************************************************

           Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FireEntry.cpp
   Author : tao.jing
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#include <QApplication>
#include <QMetaType>
#include "AppMonitor.h"
#include "FuMainWid.h"
#include "yuvframedata.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    qRegisterMetaType<YuvFrameData>("YuvFrameData");

    TF::AppMonitor::initApp(argc, argv);

    TF::FuMainWid win;
    win.show();

    return QApplication::exec();
}
