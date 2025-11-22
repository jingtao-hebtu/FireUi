/**************************************************************************

Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FuVideoPage_Ui.cpp
   Author : tao.jing
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#include "FuVideoPage_Ui.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>


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
    mVideoAreaWid = new QWidget(mWid);
    mVideoAreaWid->setObjectName("VideoAreaWid");
    QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(mVideoAreaWid->sizePolicy().hasHeightForWidth());
    mVideoAreaWid->setSizePolicy(sizePolicy);

    mVideoGLayout = new QGridLayout(mVideoAreaWid);
    mVideoGLayout->setSpacing(0);
    mVideoGLayout->setObjectName("VideoGLayout");
    mVideoGLayout->setContentsMargins(0, 0, 0, 0);

    mMainVLayout->addWidget(mVideoAreaWid);
}

void TF::FuVideoPage_Ui::initCtrlArea() {
    mCtrlHLayout = new QHBoxLayout();
    mCtrlHLayout->setSpacing(6);

    mStartVideoBtn = new QPushButton(mWid);
    mStartVideoBtn->setObjectName("StartVideo");
    mStartVideoBtn->setText("开始");
    mCtrlHLayout->addWidget(mStartVideoBtn);

    mMainVLayout->addLayout(mCtrlHLayout);
}
