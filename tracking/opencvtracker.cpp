#include "opencvtracker.h"

OpenCVTracker::OpenCVTracker() :
    _criteria(cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 40, 0)),
    _maxLevel(3),
    _winSize(cv::Size(21, 21))
{

}

OpenCVTracker::~OpenCVTracker()
{

}

mPointF OpenCVTracker::track(Image *img)
{
    std::vector<uchar> status;
    std::vector<float> err;

    OpenCVImage *cvImg = static_cast<OpenCVImage*>(img);
    cvImg->mat().copyTo(frame);

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    std::vector<cv::Point2f> oldp;
    oldp.push_back(points[0]);
    std::vector<cv::Point2f> newp;
    newp.push_back(points[1]);
    cv::calcOpticalFlowPyrLK(prevGray, gray, oldp, newp, status, err, _winSize, _maxLevel, _criteria);
    points[1] = newp.front();
    std::swap(points[1], points[0]);
    cv::swap(prevGray, gray);

    return mPointF(points[0].x, points[0].y);
}

void OpenCVTracker::setStartConfig(Image *img, mPointF pos)
{
    OpenCVImage *cvImg = static_cast<OpenCVImage*>(img);
    cvImg->mat().copyTo(frame);
    cv::cvtColor(frame, prevGray, cv::COLOR_BGR2GRAY);
    points[0].x = pos.x();
    points[0].y = pos.y();
    points[1].x = 0;
    points[1].y = 0;
}

TrackMethod OpenCVTracker::trackMethod()
{
    return OpenCVLukasKanade;
}

void OpenCVTracker::setTermCriteria(int count, double eps)
{
    _criteria = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS,
                                 count, eps);
}

void OpenCVTracker::setMaxLevel(int maxLevel)
{
    _maxLevel = maxLevel;
}

void OpenCVTracker::setWinSize(int w, int h)
{
    _winSize.width = w;
    _winSize.height = h;
}

