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
#include "videohelper.h"
#include "TConfig.h"
#include "FuVideoButtons.h"
#include <iostream>
#include <QDateTime>
#include <QDir>



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

    connect(mUi->mSaveToggleBtn, &QPushButton::toggled,
        this, &FuVideoPage::onSaveButtonToggled);
}

void TF::FuVideoPage::initVideo() {
    mVideoWid = mUi->mVideoViewer;
    //DeviceUtil::initVideoWidget2(mVideoWid);

    WidgetPara widgetPara = mVideoWid->getWidgetPara();
    //widgetPara.borderWidth = 5;
    //widgetPara.bgImage = QImage(QString("%1/config/bg_novideo.png").arg(QtHelper::appPath()));
    //widgetPara.bannerEnable = true;
    widgetPara.scaleMode = ScaleMode_Auto;
    widgetPara.videoMode = VideoMode_Hwnd;
    mVideoWid->setWidgetPara(widgetPara);

    VideoPara videoPara = mVideoWid->getVideoPara();
    videoPara.videoCore = VideoHelper::getVideoCore();
    videoPara.decodeType = DecodeType_Fast;
    videoPara.hardware = "none";
    videoPara.transport = "tcp";
    videoPara.playRepeat = false;
    videoPara.readTimeout = 0;
    videoPara.connectTimeout = 1000;
    mVideoWid->setVideoPara(videoPara);
}

void TF::FuVideoPage::onFileDrag(const QString& url) {
    VideoWidget *videoWidget = (VideoWidget *) sender();
    videoWidget->open(url);
}

void TF::FuVideoPage::onStreamButtonPressed() {
    if (!mVideoWid) {
        return;
    }

    // Start stream
    if (!mUi->mStreamToggleBtn->isChecked()) {
        if (!mRGBCamPlaying.load()) {
            auto video_url = GET_STR_CONFIG("VideoURL");
            if (mVideoWid->open(video_url.c_str())) {
                qDebug() << mVideoWid->size();
                mRGBCamPlaying.store(true);
            } else {
                mUi->mStreamToggleBtn->setChecked(false);
            }
        }
    }
    // Stop stream
    else if (mUi->mStreamToggleBtn->isChecked()) {
        if (mRGBCamPlaying.load()) {
            mVideoWid->stop();
            mRGBCamPlaying.store(false);
        }
    }
}

void TF::FuVideoPage::onSaveButtonToggled(bool checked) {
    if (!mVideoWid) {
        return;
    }

    if (checked) {
        if (!mVideoWid->getIsRunning()) {
            mUi->mSaveToggleBtn->setChecked(false);
            return;
        }

        QDir dir(QDir::currentPath());
        QString videoDir = dir.filePath("videos");
        if (!dir.exists("videos")) {
            dir.mkpath("videos");
        }

        const QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        const QString filePath = QDir(videoDir).filePath(QString("%1.mp4").arg(timestamp));
        mVideoWid->recordStart(filePath);
        mRecording.store(true);
    } else {
        if (mRecording.load()) {
            mVideoWid->recordStop();
            mRecording.store(false);
        }
    }
}
