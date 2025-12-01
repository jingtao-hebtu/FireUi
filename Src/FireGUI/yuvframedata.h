#ifndef YUVFRAMEDATA_H
#define YUVFRAMEDATA_H

#include <QByteArray>

struct YuvFrameData {
    int      width   = 0;
    int      height  = 0;
    quint32  strideY = 0;
    quint32  strideU = 0;
    quint32  strideV = 0;

    QByteArray planeY;
    QByteArray planeU;
    QByteArray planeV;
};

Q_DECLARE_METATYPE(YuvFrameData)

#endif // YUVFRAMEDATA_H
