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
#include <QStyle>

namespace TF {

    namespace {
        QToolButton* createTabButton(QWidget *parent, const QIcon &icon, const QString &tooltip) {
            auto *button = new QToolButton(parent);
            button->setCheckable(true);
            button->setAutoExclusive(true);
            button->setIcon(icon);
            button->setIconSize(QSize(32, 32));
            button->setToolTip(tooltip);
            button->setFixedSize(64, 64);
            button->setToolButtonStyle(Qt::ToolButtonIconOnly);
            button->setStyleSheet("QToolButton { border: none; background: transparent; border-radius: 8px; }"
                                  "QToolButton:hover { background-color: rgba(45, 137, 239, 30%); }"
                                  "QToolButton:checked { background-color: #2d89ef; color: white; }");
            return button;
        }
    }

    void FuSideTabBar_Ui::setupUi(QWidget *wid) {
        mWid = wid;

        mLayout = new QVBoxLayout(mWid);
        mLayout->setContentsMargins(8, 12, 8, 12);
        mLayout->setSpacing(12);

        auto *style = mWid->style();
        mButtons.append(createTabButton(mWid, style->standardIcon(QStyle::SP_ComputerIcon), QObject::tr("概览")));
        mButtons.append(createTabButton(mWid, style->standardIcon(QStyle::SP_DesktopIcon), QObject::tr("采集")));
        mButtons.append(createTabButton(mWid, style->standardIcon(QStyle::SP_FileDialogDetailedView), QObject::tr("记录")));
        mButtons.append(createTabButton(mWid, style->standardIcon(QStyle::SP_MessageBoxInformation), QObject::tr("状态")));

        for (auto *button : mButtons) {
            mLayout->addWidget(button);
        }

        mLayout->addStretch();
    }
}
