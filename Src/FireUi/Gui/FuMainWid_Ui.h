/**************************************************************************

Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FuMainWid_Ui.h
   Author : tao.jing
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#ifndef FIREUI_FUMAINWID_UI_H
#define FIREUI_FUMAINWID_UI_H

#include <QWidget>


namespace TF {

    class FuMainWid_Ui {

        friend class TVideoViewer;

    public:

        void setupUi(QWidget* wid);

    protected:

        QWidget *mWid {nullptr};

    };

};




#endif //EPVIDEOVIEWER_FUMAINWID_UI_H
