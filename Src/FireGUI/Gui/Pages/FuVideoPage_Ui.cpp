/**************************************************************************

Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FuVideoPage_Ui.cpp
   Author : tao.jing
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#include "FuVideoPage_Ui.h"
#include "videowidgetx.h"
#include <QWidget>
#include <QVBoxLayout>
#include "Gui/Controls/FuVideoButtons.h"
#include <QSpacerItem>


void TF::FuVideoPage_Ui::setupUi(QWidget* wid) {
    mWid = wid;
    mWid->resize(1000, 600);

    mMainVLayout = new QVBoxLayout(mWid);
    mMainVLayout->setSpacing(6);
    mMainVLayout->setObjectName("MainVLayout");
    mMainVLayout->setContentsMargins(6, 6, 6, 6);

    initVideoArea();
    initCtrlArea();
}

void TF::FuVideoPage_Ui::initVideoArea() {
    mVideoViewer = new VideoWidget(mWid);
    mVideoViewer->setObjectName("VideoViewer");
    mVideoViewer->resize(1000, 600);
    qDebug() << mVideoViewer->size();
    mMainVLayout->addWidget(mVideoViewer);
}

void TF::FuVideoPage_Ui::initCtrlArea() {
    mCtrlHLayout = new QHBoxLayout();
    mCtrlHLayout->setSpacing(12);
    mCtrlHLayout->setContentsMargins(10, 10, 10, 10);

    mStreamToggleBtn = new TechToggleButton("主相机", mWid);
    mStreamToggleBtn->setObjectName("StartStopStream");

    mAiToggleBtn = new TechToggleButton("AI检测", mWid);
    mAiToggleBtn->setObjectName("StartStopAi");

    mSaveToggleBtn = new TechToggleButton("保存视频", mWid);
    mSaveToggleBtn->setObjectName("StartStopSave");

    mRefreshOnceBtn = new TechActionButton("刷新显示", mWid);
    mRefreshOnceBtn->setObjectName("RefreshOnce");

    mCtrlHLayout->addWidget(mStreamToggleBtn);
    mCtrlHLayout->addWidget(mAiToggleBtn);
    mCtrlHLayout->addWidget(mSaveToggleBtn);
    mCtrlHLayout->addWidget(mRefreshOnceBtn);
    mCtrlHLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    mMainVLayout->addLayout(mCtrlHLayout);
}
