/**************************************************************************

Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FuVideoPage.cpp
   Author : tao.jing
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#include "FuVideoPage.h"
#include "FuVideoPage_Ui.h"
#include "devicetree.h"
#include "videobox.h"
#include "videowidgetx.h"
#include "deviceutil.h"
#include "qthelper.h"
#include "TConfig.h"
#include "FuVideoButtons.h"
#include <iostream>



TF::FuVideoPage::FuVideoPage(QWidget* parent) : QWidget(parent) {
    setupUI();
}

TF::FuVideoPage::~FuVideoPage() {

}

void TF::FuVideoPage::setupUI() {
    mUi = new FuVideoPage_Ui();
    mUi->setupUi(this);

    initVideo();
    initActions();
}

void TF::FuVideoPage::initActions() {
    connect(mUi->mStreamToggleBtn, &QPushButton::pressed,
        this, &FuVideoPage::onStreamButtonPressed);
}

void TF::FuVideoPage::initVideo() {
    mVideoSelect = nullptr;
    mVideoWids.clear();

    QWidgetList widgets;
    for (int i = 0; i < mVideoNum; ++i) {
        auto *video_wid = new VideoWidget;
        connect(video_wid, SIGNAL(sig_fileDrag(QString)), this, SLOT(onFileDrag(QString)));
        DeviceUtil::initVideoWidget2(video_wid);
        video_wid->installEventFilter(this);
        video_wid->hideButton();
        video_wid->setBgText(QString("通道 %1").arg(i + 1, 2, 10, QChar('0')));
        widgets << video_wid;
        mVideoWids << video_wid;
    }

    mIsMax = false;
    mVideoMenu = new QMenu(this);
    mVideoSelect = mVideoWids.first();

    mVideoBox = new VideoBox(this);
    mVideoBox->setLayout(mUi->mVideoGLayout);
    mVideoBox->setLayoutType("1-1");
    mVideoBox->initMenu(mVideoMenu);
    mVideoBox->setWidgets(widgets);
    mVideoBox->show_all();
}

void TF::FuVideoPage::onFileDrag(const QString& url) {
    VideoWidget *videoWidget = (VideoWidget *) sender();
    videoWidget->open(url);
}

void TF::FuVideoPage::onStreamButtonPressed() {
    if (!mVideoSelect) {
        return;
    }

    // Start stream
    if (!mUi->mStreamToggleBtn->isChecked()) {
        if (!mRGBCamPlaying.load()) {
            std::string video_url = GET_STR_CONFIG("VideoURL");
            if (mVideoSelect->open(video_url.c_str())) {
                mRGBCamPlaying.store(true);
            } else {
                mUi->mStreamToggleBtn->setChecked(false);
            }
        }
    }
    // Stop stream
    else if (mUi->mStreamToggleBtn->isChecked()) {
        if (mRGBCamPlaying.load()) {
            mVideoSelect->stop();
            mRGBCamPlaying.store(false);
        }
    }
}
