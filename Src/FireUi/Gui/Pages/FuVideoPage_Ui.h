/**************************************************************************

Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FuVideoPage_Ui.h
   Author : tao.jing
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#ifndef FIREUI_FUVIDEOPAGE_UI_H
#define FIREUI_FUVIDEOPAGE_UI_H
#include <QHBoxLayout>


class QWidget;
class QVBoxLayout;
class QGridLayout;
class QPushButton;

namespace TF {
    class FuVideoPage_Ui
    {
        friend class FuVideoPage;

    public:
        void setupUi(QWidget* wid);

    private:
        void initVideoArea();

        void initCtrlArea();

    private:
        QWidget* mWid{nullptr};
        QVBoxLayout* mMainVLayout{nullptr};

        QHBoxLayout* mCtrlHLayout{nullptr};
        QPushButton* mStartVideoBtn{nullptr};

        QWidget* mVideoAreaWid{nullptr};
        QGridLayout* mVideoGLayout{nullptr};
    };
} // TF

#endif //FIREUI_FUVIDEOPAGE_UI_H
