#ifndef TRACKER_H
#define TRACKER_H

#include "objects/image.h"
#include "utils/point.h"
#include "utils/size.h"
#include "gaussianblur.h"

enum TrackMethod { Template, OpenCVLukasKanade };

class Tracker
{
public:
    Tracker() : needBlur(true) { gaussianBlur.updateKernel(0.85, 5); }
    virtual ~Tracker() { }
    virtual mPointF track(Image *) = 0;
    virtual void setStartConfig(Image *img, mPointF pos) = 0;

    virtual TrackMethod trackMethod() { return method; }

    virtual void setBlur(bool value) { needBlur = value; }
    virtual bool blur() { return needBlur; }

    virtual double sigma() { return gaussianBlur.sigma(); }
    virtual int kernelSize() { return gaussianBlur.kernelSize(); }

    virtual void setBlurParams(double sigma, int size)
    { gaussianBlur.updateKernel(sigma, size); }

protected:
    TrackMethod method;
    GaussianBlur gaussianBlur;
    bool needBlur;
};

#endif // TRACKER_H
