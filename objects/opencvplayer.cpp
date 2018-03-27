#include "opencvplayer.h"

OpenCVPlayer::OpenCVPlayer() :
    capture(nullptr), _state(Pause)
{

}

OpenCVPlayer::~OpenCVPlayer()
{
    _state = Stop;
    capture->release();
    delete capture;
    exit();
}

bool OpenCVPlayer::setMedia(const std::string &fileName)
{
    capture = new cv::VideoCapture(fileName);

    if (capture->isOpened())
    {
        frameRate = capture->get(CV_CAP_PROP_FPS);
        emit durationChanged((long long)capture->get(CV_CAP_PROP_FRAME_COUNT)*1000/frameRate+0.5);
        return readNextFrame();
    }
    return false;
}

void OpenCVPlayer::play()
{
    if (_state == Play)
        _state = Pause;
    else
        _state = Play;

    emit mediaStateChanged(_state);

    if (!isRunning())
        start(LowPriority);
}

void OpenCVPlayer::stop()
{
    if (_state == Stop)
        return;

    _state = Stop;
    emit mediaStateChanged(_state);
    if (capture->set(CV_CAP_PROP_POS_FRAMES, 0))
    {
        if (readNextFrame())
            capture->set(CV_CAP_PROP_POS_FRAMES, 0);
    }
}

void OpenCVPlayer::setPosition(long long msec)
{
    if (capture->set(CV_CAP_PROP_POS_MSEC, msec))
        readNextFrame();
}

long long OpenCVPlayer::duration() const
{
    return capture->get(CV_CAP_PROP_FRAME_COUNT)*1000./frameRate;
}

double OpenCVPlayer::fps() const
{
    return frameRate;
}

double OpenCVPlayer::time() const
{
     return capture->get(CV_CAP_PROP_POS_MSEC);
}

void OpenCVPlayer::setFRS(double fps)
{
    frameRate = fps;
}

int OpenCVPlayer::currentFrameNumber()
{
    return (int) capture->get(CV_CAP_PROP_POS_FRAMES);
}

cv::Mat OpenCVPlayer::ImageAt(int pos, bool *ok)
{
    pos--;
    if (pos < 0 || pos >= capture->get(CV_CAP_PROP_FRAME_COUNT))
    {
        *ok = false;
        return cv::Mat();
    }

    *ok = true;

    int lastPos = currentFrameNumber();
    cv::Mat tmp;
    capture->set(CV_CAP_PROP_POS_FRAMES, pos);
    capture->read(tmp);
    capture->set(CV_CAP_PROP_POS_FRAMES, lastPos);
    return tmp;
}

void OpenCVPlayer::setFrame(int pos)
{
    capture->set(CV_CAP_PROP_POS_FRAMES, pos);
}

void OpenCVPlayer::run()
{
    int delay = 1000/frameRate;
    while(_state == Play)
    {
        if (readNextFrame())
            msleep(delay);
        else
        {
            _state = Stop;
            capture->set(CV_CAP_PROP_POS_FRAMES, 0);
        }
    }
}

bool OpenCVPlayer::readNextFrame()
{
    qRegisterMetaType <State> ("State");
    emit positionChanged((long long)capture->get(CV_CAP_PROP_POS_MSEC)+0.5);

    if (!capture->read(frame))
    {
        _state = Stop;
        emit mediaStateChanged(_state);
        return false;
    }

    if (frame.channels()== 3)
    {
        cv::cvtColor(frame, RGBframe, CV_BGR2RGB);

        img = QImage((const unsigned char*)(RGBframe.data),
                      RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
    }
    else
    {
        img = QImage((const unsigned char*)(frame.data),
                      frame.cols,frame.rows,QImage::Format_Indexed8);
    }

    emit processedImage(img);
    emit processedCVImage(frame);

    return true;
}

bool OpenCVPlayer::readPrevFrame()
{
    int nextFrame = (int) capture->get(CV_CAP_PROP_POS_FRAMES);
    if (nextFrame < 2)
        return false;
    else
    {
        capture->set(CV_CAP_PROP_POS_FRAMES, nextFrame-2);
        readNextFrame();
    }
    return true;
}
