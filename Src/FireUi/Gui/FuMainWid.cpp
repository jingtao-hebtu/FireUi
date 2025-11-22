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


TF::FuMainWid::FuMainWid(QWidget* parent) : QWidget(parent) {
    setupUi();
}

TF::FuMainWid::~FuMainWid() {
    delete mUi;
}

void TF::FuMainWid::setupUi() {
    mUi = new FuMainWid_Ui();
    mUi->setupUi(this);
}
