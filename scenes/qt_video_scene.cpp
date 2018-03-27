#include "qt_video_scene.h"

QtVideoScene::QtVideoScene(QObject *parent) :
    QObject(parent)
{
    connect(static_cast<QtVideoPlayer*>(player), SIGNAL(positionChanged(qint64)),
            this, SIGNAL(positionChanged(qint64)));  //fix me
}

