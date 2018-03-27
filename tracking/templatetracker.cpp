#include "templatetracker.h"
#include "objects/trackpoint_item.h"

#include <math.h>
int TemplateTracker::correlation(const Image *frame, int u, int v)
{
    int sum = 0;
    for (int i = 0; i < _templateSize.h; i++)
        for (int t = 0; t < _templateSize.w; t++)
            sum += abs(frame->intensity(i+u,t+v) - templ->intensity(i,t));
    return sum;
}

mPointI TemplateTracker::templateSearch(const Image *frame)
{
    int sum, a = 0, b = 0;
    int Eps = INT_MAX;
    for (int u = 0; u <= frame->height() - _templateSize.h; u++)
    {
        for (int v = 0; v <= frame->width() - _templateSize.w; v++)
        {
            sum = correlation(frame, u, v);
            if (sum < Eps)
            {
                Eps = sum;
                a = u;
                b = v;
            }
        }
    }
    return mPointI(b, a);
}

mPointF solve(float A[2][2], float *B)
{
    float D = A[0][0]*A[1][1] - A[0][1]*A[1][0];
    float Dx = B[0]*A[1][1] - A[0][1]*B[1];
    float Dy = B[1]*A[0][0] - A[1][0]*B[0];
    if (D != 0)
        return mPointF(Dx/D, Dy/D);
    else
        return mPointF(0, 0);
}

#include "derivativecentral.h"

mPointF TemplateTracker::rectification(const Image *frame)
{
    float B[2];
    B[0] = B[1] = 0;
    int e = 0;

    for (int i = 0; i < templ->height(); i++)
    {
        for (int j = 0; j < templ->width(); j++)
        {
            e = frame->intensity(i,j) - templ->intensity(i,j);
            B[0] -= derXTempl(i,j)*e;
            B[1] -= derYTempl(i,j)*e;
        }
    }
    return solve(A, B);
}

TemplateTracker::TemplateTracker()
{
    method = Template; _templateSize = {10,10};
    _imageSize = {30,30};
}

mPointF TemplateTracker::track(Image *frame)
{
    if (frame->width() < _imageSize.w || frame->height() < _imageSize.h)
        return mPointF(0,0);
    if (_templateSize.w > _imageSize.w || _templateSize.h > _imageSize.h)
        return mPointF(0,0);

    mPointI imagePos = templPos - mPointI((_imageSize.w-_templateSize.w)/2,
                                                (_imageSize.h-_templateSize.h)/2);
    if (imagePos.x() < 0)
        imagePos.setX(0);
    if (imagePos.y() < 0)
        imagePos.setY(0);
    int t = frame->width() - _imageSize.w - 1;
    if (imagePos.x() > t)
        imagePos.setX(t);
    t = frame->height() - _imageSize.h - 1;
    if (imagePos.y() > t)
        imagePos.setY(t);

    Image *image = frame->piece(imagePos, _imageSize.w, _imageSize.h);
    if (needBlur)
        gaussianBlur.blur(image);

    mPointI resPoint = templateSearch(image);
    Image *result = image->piece(resPoint, _templateSize.w, _templateSize.h);
    mPointF delta = rectification(result);

    resPoint += imagePos;
    delta += resPoint;
    templPos.setX(int(delta.x() + 0.5));
    templPos.setY(int(delta.y() + 0.5));

    image->clear();
    result->clear();

    return delta;
}

void TemplateTracker::setStartConfig(Image *img, mPointF pos)
{
    Image *tmp = img->copy();

    if (needBlur)
        gaussianBlur.blur(tmp);

    templ = tmp->piece(pos, _templateSize.w, _templateSize.h);
    templPos = pos;

    derXTempl.resize(_templateSize.h, _templateSize.w);
    derYTempl.resize(_templateSize.h, _templateSize.w);
    A[0][0] = A[1][1] = A[1][0] = A[0][1] = 0;

    for (int i = 0; i < _templateSize.h; i++)
    {
        for (int j = 0; j < _templateSize.w; j++)
        {
            uchar color = templ->intensity(i, j);

            if (j == _templateSize.w-1)
                derXTempl(i,j) = tmp->intensity(pos.y()+i, pos.x()+j+1)-color;
            else
                derXTempl(i,j) = templ->intensity(i, j+1) - color;

            if (i == _templateSize.h-1)
                derYTempl(i,j) = tmp->intensity(pos.y()+i+1, pos.x()+j) - color;
            else
                derYTempl(i,j) = templ->intensity(i+1, j) - color;

            A[0][0] += pow(derXTempl(i,j),2);
            A[0][1] += derXTempl(i,j) * derYTempl(i,j);
            A[1][1] += pow(derYTempl(i,j),2);

        }
    }

    A[1][0] = A[0][1];

    tmp->clear();
}
