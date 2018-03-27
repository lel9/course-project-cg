#ifndef RGB_H
#define RGB_H

#include <QRgb>
class Rgb
{
private:
    float _red;
    float _green;
    float _blue;
public:
    Rgb() : _red(0), _green(0), _blue(0) { }
    Rgb(float red, float green, float blue) : _red(red), _green(green), _blue(blue) { }
    ~Rgb() = default;
    float red() const { return _red; }
    float green() const { return _green; }
    float blue() const { return _blue; }

    QRgb toQRgb() const
    {
        int r = _red < 0 ? 0 : (_red > 255 ? 255 : _red + 0.5);
        int g = _green < 0 ? 0 : (_green > 255 ? 255 : _green + 0.5);
        int b = _blue < 0 ? 0 : (_blue > 255 ? 255 : _blue + 0.5);
        return qRgb(r, g, b);
    }

    Rgb operator+(const Rgb&other) const;
    Rgb operator-(const Rgb &other) const;
    Rgb operator*(const double factor) const;
    Rgb operator*(const Rgb &other) const;
    Rgb& operator +=(const Rgb &other);
    Rgb& operator -=(const Rgb &other);
};

#endif // RGB_H
