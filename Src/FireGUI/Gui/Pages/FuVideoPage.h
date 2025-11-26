/**************************************************************************

Copyright(C), tao.jing All rights reserved

 **************************************************************************
   File   : FuVideoPage.h
   Author : tao.jing
   Date   : 2025/11/22
   Brief  :
**************************************************************************/
#ifndef FIREUI_FUVIDEOPAGE_H
#define FIREUI_FUVIDEOPAGE_H

#include <QWidget>
#include <QString>
#include "../../../ThirdParty/TVideoSystem/VideoBase/widgetstruct.h"
#include <atomic>

class VideoBox;

class VideoWidget;

struct WidgetPara;

struct VideoPara;


namespace TF {
    class FuVideoPage_Ui;

    class FuVideoPage : public QWidget
    {

        Q_OBJECT

    public:
        explicit FuVideoPage(QWidget* parent = nullptr);

        ~FuVideoPage() final;

    public:
        VideoWidget* getVideoWid() {return mVideoWid;}

    private slots:
        void onFileDrag(const QString &url);

        void onStreamButtonPressed();

        void onSaveButtonToggled(bool checked);

        void onAiButtonToggled(bool checked);

    private:
        void setupUI();

        void initActions();

        void initVideo();

        void applyDisplayMode(bool aiEnabled);

    private:
        FuVideoPage_Ui* mUi;

        bool mIsMax;

        VideoWidget *mVideoWid {nullptr};

        static const int mVideoNum = 1;

        std::atomic<bool> mRGBCamPlaying {false};

        std::atomic<bool> mRecording {false};

        WidgetPara mGpuWidgetPara;
        WidgetPara mCpuWidgetPara;
        VideoPara mGpuVideoPara;
        VideoPara mCpuVideoPara;
        QString mCurrentUrl;
        bool mAiEnabled {false};
    };
} // TF

#endif //FIREUI_FUVIDEOPAGE_H
