/**************************************************************************

Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FuSideTabBar_Ui.cpp
   Author : OpenAI ChatGPT
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#include "FuSideTabBar_Ui.h"

#include <QObject>
#include <QIcon>
#include <QSize>

namespace TF {

    namespace {
        QToolButton* createTabButton(QWidget *parent, const QIcon &icon, const QString &tooltip) {
            auto *button = new QToolButton(parent);
            button->setCheckable(true);
            button->setAutoExclusive(true);
            button->setIcon(icon);
            button->setIconSize(QSize(30, 30));
            button->setToolTip(tooltip);
            button->setFixedSize(72, 68);
            button->setToolButtonStyle(Qt::ToolButtonIconOnly);
            button->setProperty("sideTab", true);
            return button;
        }
    }

    void FuSideTabBar_Ui::setupUi(QWidget *wid) {
        mWid = wid;
        mWid->setObjectName("SideTabBar");

        mLayout = new QVBoxLayout(mWid);
        mLayout->setContentsMargins(8, 12, 8, 12);
        mLayout->setSpacing(12);

        struct TabInfo {
            QString iconPath;
            QString tooltip;
        };

        const QVector<TabInfo> tabs = {
                {QStringLiteral(":/icons/nav-dashboard.svg"), QObject::tr("概览")},
                {QStringLiteral(":/icons/nav-control.svg"), QObject::tr("采集")},
                {QStringLiteral(":/icons/nav-logs.svg"), QObject::tr("记录")},
                {QStringLiteral(":/icons/nav-status.svg"), QObject::tr("状态")},
        };

        for (const auto &tab : tabs) {
            mButtons.append(createTabButton(mWid, QIcon(tab.iconPath), tab.tooltip));
        }

        for (auto *button : mButtons) {
            mLayout->addWidget(button);
        }

        mLayout->addStretch();
    }
}
