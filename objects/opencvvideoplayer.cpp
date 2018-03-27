#include "opencvvideoplayer.h"

#include "videoitem.h"
OpenCVVideoPlayer::OpenCVVideoPlayer()
{
    player = new OpenCVPlayer;
}

OpenCVVideoPlayer::~OpenCVVideoPlayer()
{
    delete player;
}

void OpenCVVideoPlayer::setItem(const shared_ptr<Item> &item)
{
    qRegisterMetaType<cv::Mat>("cv::Mat");

    VideoPlayer::setItem(item);
    QObject::connect(player, SIGNAL(processedImage(QImage)),
                     _item.get(),   SLOT  (setImage(QImage)));
    QObject::connect(player, SIGNAL(processedCVImage(cv::Mat)),
                     this,   SLOT  (on_processedImage(cv::Mat)));
    QObject::connect(player, SIGNAL(mediaStateChanged(State)),
                     this,   SLOT  (on_mediaStateChanged(State)));
    QObject::connect(player, SIGNAL(positionChanged(qint64)),
                     this,   SIGNAL(positionChanged(qint64)));
    QObject::connect(player, SIGNAL(durationChanged(qint64)),
                     this,   SIGNAL(durationChanged(qint64)));

}

bool OpenCVVideoPlayer::setMedia(const std::string &fileName)
{
    return player->setMedia(fileName);
}

void OpenCVVideoPlayer::play()
{
    player->play();
}

void OpenCVVideoPlayer::stop()
{
    player->stop();
}

void OpenCVVideoPlayer::goToNextFrame()
{
    if (_state != Play)
        player->readNextFrame();
}

void OpenCVVideoPlayer::goToPrevFrame()
{
    if (_state != Play)
        player->readPrevFrame();
}

void OpenCVVideoPlayer::setPosition(qint64 msec)
{
    if (_state != Play)
        player->setPosition(msec);
}

qint64 OpenCVVideoPlayer::duration() const
{
    return player->duration();
}

bool OpenCVVideoPlayer::isPlaying()
{
    if (_state == Play)
        return true;
    return false;
}

void OpenCVVideoPlayer::setFPS(double fps)
{
    player->setFRS(fps);
}

double OpenCVVideoPlayer::FPS() const
{
    return player->fps();
}

#include "utils/converter.h"
QTime OpenCVVideoPlayer::currentTime()
{
    return TimeConverter::msecToQTime(player->time());
}

#include "opencvimage.h"
Image *OpenCVVideoPlayer::currentFrame()
{
    Image *myImg = new OpenCVImage(player->currentImage());
    return myImg;
}

int OpenCVVideoPlayer::currentFrameNumber()
{
    return player->currentFrameNumber();
}

Image* OpenCVVideoPlayer::frame(int pos, bool *ok)
{
    cv::Mat img = player->ImageAt(pos, ok);
    if (!(*ok))
        return nullptr;
    Image *myImg = new OpenCVImage(img);
    return myImg;
}

void OpenCVVideoPlayer::setFrame(int pos)
{
    player->setFrame(pos);
}

void OpenCVVideoPlayer::on_mediaStateChanged(State state)
{
    _state = state;
    emit mediaStateChanged(_state);
}

#include <QMetaMethod>
void OpenCVVideoPlayer::on_processedImage(cv::Mat img)
{
    if (isSignalConnected(QMetaMethod::fromSignal(OpenCVVideoPlayer::frameChanged)))
    {
        Image *myImg = new OpenCVImage(img);
        emit frameChanged(myImg);
    }
}
