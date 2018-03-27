#ifndef OPENCVVIDEOPLAYER_H
#define OPENCVVIDEOPLAYER_H

#include "opencvplayer.h"
#include "videoplayer.h"

class OpenCVVideoPlayer : public VideoPlayer
{
    Q_OBJECT

public:
    OpenCVVideoPlayer();
    ~OpenCVVideoPlayer();
    virtual void setItem(const shared_ptr<Item> &item) override;

public slots:
    virtual bool setMedia(const std::string &fileName) override;
    virtual void play() override;
    virtual void stop() override;
    virtual void goToNextFrame() override;
    virtual void goToPrevFrame() override;
    virtual void setPosition(qint64 msec) override;
    virtual qint64 duration() const override;
    virtual bool isPlaying() override;
    virtual void setFPS(double fps) override;
    virtual double FPS() const override;

    virtual QTime currentTime() override;
    virtual Image *currentFrame() override;
    virtual int currentFrameNumber() override;
    virtual Image *frame(int pos, bool *ok) override;
    virtual void setFrame(int pos) override;

private slots:
    void on_mediaStateChanged(State state);
    void on_processedImage(cv::Mat img);

private:
    OpenCVPlayer *player;

};

#endif // OPENCVVIDEOPLAYER_H
