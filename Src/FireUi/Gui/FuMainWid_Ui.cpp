/**************************************************************************

Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FuMainWid_Ui.cpp
   Author : tao.jing
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#include "FuMainWid_Ui.h"
#include "FuVideoPage.h"

#include <QLabel>
#include <QObject>
#include <QStackedWidget>
#include <QVBoxLayout>


void TF::FuMainWid_Ui::setupUi(QWidget *wid) {
    mWid = wid;
    mWid->setObjectName("FuMainWid");
    mWid->resize(1200, 720);

    mLayout = new QHBoxLayout(mWid);
    mLayout->setContentsMargins(0, 0, 0, 0);
    mLayout->setSpacing(0);

    mSideTabBar = new FuSideTabBar(mWid);
    mSideTabBar->setObjectName("SideTabBar");
    mSideTabBar->setFixedWidth(70);
    mStackedWidget = new QStackedWidget(mWid);

    auto createPage = [](const QString &title, const QString &desc) {
        auto *page = new QWidget();
        auto *layout = new QVBoxLayout(page);
        layout->setAlignment(Qt::AlignCenter);

        auto *titleLabel = new QLabel(title, page);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setProperty("title", true);

        auto *descLabel = new QLabel(desc, page);
        descLabel->setAlignment(Qt::AlignCenter);
        descLabel->setProperty("description", true);

        layout->addWidget(titleLabel);
        layout->addWidget(descLabel);
        return page;
    };

    mVideoPage = new FuVideoPage();
    mVideoPage->setObjectName("VideoPage");
    mStackedWidget->addWidget(mVideoPage);

    mStackedWidget->addWidget(createPage(QObject::tr("采集"), QObject::tr("双光火焰采集控制")));
    mStackedWidget->addWidget(createPage(QObject::tr("记录"), QObject::tr("历史记录与回放")));
    mStackedWidget->addWidget(createPage(QObject::tr("状态"), QObject::tr("当前运行状态详情")));

    mLayout->addWidget(mSideTabBar);
    mLayout->addWidget(mStackedWidget);
    mLayout->setStretch(1, 1);
}
