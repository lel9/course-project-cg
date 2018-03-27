#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "scene_object.h"

#include <string>

enum State { Play, Pause, Stop };

class VideoPlayer : public SceneObject
{
    Q_OBJECT

public:
    VideoPlayer() : _state(Stop) { }
    virtual ~VideoPlayer() = default;

    virtual bool setMedia(const std::string &fileName) = 0;
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void goToNextFrame() = 0;
    virtual void goToPrevFrame() = 0;
    virtual void setPosition(qint64 position) = 0;
    virtual qint64 duration() const = 0;
    virtual bool isPlaying() = 0;
    virtual void setFPS(double fps) = 0;
    virtual double FPS() const = 0;

    virtual bool isVideo() override { return true; }

    virtual QTime currentTime() = 0;
    virtual Image *currentFrame() = 0;
    virtual int currentFrameNumber() = 0;
    virtual void setFrame(int) = 0;
    virtual Image *frame(int, bool*) = 0;

signals:
    void frameChanged(Image *img);
    void mediaStateChanged(State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);

protected:
    State _state;
};


#endif // VIDEOPLAYER_H
