#ifndef OPENCVTRACKER_H
#define OPENCVTRACKER_H

#include "tracker.h"
#include "objects/opencvimage.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/video/tracking.hpp"

class OpenCVTracker : public Tracker
{
public:
    OpenCVTracker();
    ~OpenCVTracker();
    virtual mPointF track(Image *img);
    virtual void setStartConfig(Image *img, mPointF pos) override;

    virtual TrackMethod trackMethod() override;

    int maxLevel() { return _maxLevel; }
    int winSizeWidth() { return _winSize.width; }
    int winSizeHeight() { return _winSize.height; }
    int TCCount() { return _criteria.maxCount; }
    double TCEps() { return _criteria.epsilon; }

    void setTermCriteria(int count, double eps);
    void setMaxLevel(int maxLevel);
    void setWinSize(int w, int h);

private:
    cv::Mat gray, prevGray, frame;
    cv::Point2f points[2];

    cv::TermCriteria _criteria;
    int _maxLevel;
    cv::Size _winSize;
};

#endif // OPENCVTRACKER_H
