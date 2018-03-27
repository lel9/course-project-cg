#ifndef TEMPLATETRACKER_H
#define TEMPLATETRACKER_H

#include "tracker.h"

#include <QVector>
class TemplateTracker : public Tracker
{
public:
    TemplateTracker();
    virtual ~TemplateTracker() { }

    virtual mPointF track(Image *frame) override;
    virtual void setStartConfig(Image *img, mPointF pos) override;

    void setTemplateSize(const Size &size) { _templateSize = size; }
    void setImageSize(const Size &size) {  _imageSize = size; }

    Size templateSize() { return _templateSize; }
    Size imageSize() { return _imageSize; }

protected:
    mPointI templateSearch(const Image *frame);
    mPointF rectification(const Image *frame);
    int correlation(const Image *frame, int u, int v);

private:
    Image *templ;
    mPointI templPos;

    Matrix<double> derXTempl;
    Matrix<double> derYTempl;
    float A[2][2];

    Size _templateSize;
    Size _imageSize;
};

#endif // TEMPLATETRACKER_H
