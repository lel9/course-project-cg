#include "video_scene.h"
#include "utils/converter.h"

VideoScene::VideoScene()
{
}

VideoScene::~VideoScene()
{
}

void VideoScene::setCanvas(Canvas *canvas)
{
    connect(canvas, SIGNAL(updateCursorPos(QPointF)),
            this, SIGNAL(updateCursorPos(QPointF)));
    Scene::setCanvas(canvas);
}

void VideoScene::addChild(const shared_ptr<SceneObject> &child)
{
    Scene::addChild(child);
    if (!_player.expired())
        child->setStartFrame(_player.lock()->currentFrame());
}

void VideoScene::stop()
{
    if (!_player.expired())
    {
        shared_ptr<VideoPlayer> player = _player.lock();
        disconnect(player.get(), SIGNAL(frameChanged(Image*)),
                   this, SLOT(updateTrackPoint(Image*)));
        player->stop();
        _canvas->setEnabled(true);
    }
}

void VideoScene::goToNextFrame()
{
    if (!_player.expired())
        _player.lock()->goToNextFrame();
}

void VideoScene::goToPrevFrame()
{
    if (!_player.expired())
        _player.lock()->goToPrevFrame();
}

#include "objects/trackpoint_item.h"

void VideoScene::track()
{
    if (_player.expired())
        return;

    shared_ptr<VideoPlayer> player = _player.lock();
    if (!player->isPlaying())
    {
        connect(player.get(), SIGNAL(frameChanged(Image*)),
                this, SLOT(updateTrackPoint(Image*)));

        int n = player->currentFrameNumber();

        for (auto child = _children.begin(); child < _children.end(); child++)
        {
            (*child)->setStartFrame(player->currentFrame());
            bool ok = true;
            QVector<QPointF> pos;
            for (int i = 1; i <= 3 && ok; i++)
            {
                Image* img = player->frame(n-i, &ok);
                if (ok)
                    pos << (*child)->getObjectPos(img);
            }
            (*child)->setPrevPositions(pos);
        }
        if (n > 0)
            player->setFrame(n-1);
        player->goToNextFrame();
        _canvas->setEnabled(false);
        player->play();
    }
    else
    {
        disconnect(player.get(), SIGNAL(frameChanged(Image*)),
                   this, SLOT(updateTrackPoint(Image*)));

        player->play();

        int n = player->currentFrameNumber();

        for (auto child = _children.begin(); child < _children.end(); child++)
        {
            bool ok = true;
            QVector<QPointF> pos;
            for (int i = 1; i <= 3 && ok; i++)
            {
                Image* img = player->frame(n+i, &ok);
                if (ok)
                    pos << (*child)->getObjectPos(img);
            }
            (*child)->setNextPositions(pos);
        }
        _canvas->setEnabled(true);
    }
}

#include "qt_video_canvas.h"
void VideoScene::registerPlayer(const shared_ptr<SceneObject> &player)
{
    shared_ptr<VideoPlayer> vplayer = static_pointer_cast<VideoPlayer>(player);
    emit playerChanged(vplayer);
    _player = vplayer;

    connect(vplayer.get(), SIGNAL(durationChanged(qint64)),
            this, SLOT(setVideoDuration(qint64)));
    connect(vplayer.get(), SIGNAL(positionChanged(qint64)),
            this, SLOT(on_videoPositionChanged(qint64)));

    connect(_canvas, SIGNAL(sliderReleased(qint64)), this, SLOT(setVideoPosition(qint64)));

    _canvas->registerVideoItem(vplayer->item());
}

void VideoScene::setFPS(double fps)
{
    if (!_player.expired())
        _player.lock()->setFPS(fps);
}

double VideoScene::FPS()
{
    if (_player.expired())
        return 0;
    return _player.lock()->FPS();
}

bool VideoScene::isPlaying()
{
    if (_player.expired())
        return false;
    return _player.lock()->isPlaying();
}

void VideoScene::disconnectp()
{
    shared_ptr<VideoPlayer> player = _player.lock();
    disconnect(player.get(), SIGNAL(frameChanged(Image*)),
               this, SLOT(updateTrackPoint(Image*)));
}

bool VideoScene::loadDataFromFile(const QString &filename)
{
     if (_player.expired())
         return false;
     bool res = _player.lock()->setMedia(filename.toStdString());
     if (res)
        _canvas->widget()->repaint();
     return res;
}

void VideoScene::updateTrackPoint(Image *img)
{
    for (auto child = _children.begin(); child < _children.end(); child++)
        (*child)->findObjectPos(img);
}

void VideoScene::setVideoDuration(qint64 duration)
{
    _canvas->updateTotalTime(TimeConverter::msecToQTime(duration));
}

void VideoScene::on_videoPositionChanged(qint64 pos)
{
    _canvas->updateCurrentTime(TimeConverter::msecToQTime(pos));
}

void VideoScene::setVideoPosition(qint64 pos)
{
     if (_player.expired())
         return;

    _player.lock()->setPosition(pos);
    on_videoPositionChanged(pos);
}
