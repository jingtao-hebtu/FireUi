/**************************************************************************

Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FuMainWid.cpp
   Author : tao.jing
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#include "FuMainWid.h"
#include "FuMainWid_Ui.h"
#include <QFile>


TF::FuMainWid::FuMainWid(QWidget* parent) : QWidget(parent) {
    setupUi();
    setupConnections();
    initStyle();
}

TF::FuMainWid::~FuMainWid() {
    delete mUi;
}

void TF::FuMainWid::setupUi() {
    mUi = new FuMainWid_Ui();
    mUi->setupUi(this);
}

void TF::FuMainWid::setupConnections() {
    if (mUi == nullptr) {
        return;
    }

    connect(mUi->mSideTabBar, &FuSideTabBar::tabSelected, this, [this](int index) {
        if (mUi->mStackedWidget != nullptr) {
            mUi->mStackedWidget->setCurrentIndex(index);
        }
    });

    mUi->mSideTabBar->setCurrentIndex(0);
}

void TF::FuMainWid::initStyle() {
    QFile win_style_file(QString(":/qss/wid/FuMainWid.css"));
    if (win_style_file.open(QFile::ReadOnly)) {
        QString styleStr = win_style_file.readAll();
        setStyleSheet(styleStr);
        win_style_file.close();
    }
}
