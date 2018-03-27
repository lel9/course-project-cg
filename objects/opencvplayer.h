#ifndef OPENCVPLAYER_H
#define OPENCVPLAYER_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class Video;

#include <QThread>
#include <QImage>

#include "videoplayer.h" //state

class OpenCVPlayer : public QThread
{
    Q_OBJECT

public:
    OpenCVPlayer();
    ~OpenCVPlayer();

    virtual long long duration() const;
    virtual double fps() const;
    virtual double time() const;
    virtual void setFRS(double fps);
    virtual int currentFrameNumber();
    virtual cv::Mat ImageAt(int pos, bool *ok);
    virtual void setFrame(int pos);
    virtual cv::Mat currentImage() { return frame; }

public slots:
    virtual bool setMedia(const std::string &fileName);
    virtual void play();
    virtual void stop();
    virtual bool readNextFrame();
    virtual bool readPrevFrame();

    virtual void setPosition(long long msec);

signals:
    void mediaStateChanged(State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void processedImage(QImage img);
    void processedCVImage(cv::Mat cvFrame);

protected:
     void run();

private:
     cv::Mat frame;
     double frameRate;
     cv::VideoCapture *capture;
     cv::Mat RGBframe;
     QImage img;
     State _state;
};

#endif // OPENCVPLAYER_H
