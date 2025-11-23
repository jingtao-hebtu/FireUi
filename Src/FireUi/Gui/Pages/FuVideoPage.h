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


class VideoBox;

class VideoWidget;


namespace TF {
    class FuVideoPage_Ui;

    class FuVideoPage : public QWidget
    {

        Q_OBJECT

    public:
        explicit FuVideoPage(QWidget* parent = nullptr);

        ~FuVideoPage() final;

    private slots:
        void onFileDrag(const QString &url);

        void onStartVideoBtnClicked();

    private:
        void setupUI();

        void initActions();

        void initVideo();

    private:
        FuVideoPage_Ui* mUi;

        bool mIsMax;

        QMenu *mVideoMenu;
        VideoBox *mVideoBox;
        VideoWidget *mVideoSelect;
        QList<VideoWidget*> mVideoWids;

        static const int mVideoNum = 1;

    };
} // TF

#endif //FIREUI_FUVIDEOPAGE_H
