#include "rgb.h"

Rgb Rgb::operator+(const Rgb &other) const
{
    return Rgb(_red+other.red(), _green+other.green(), _blue+other.blue());
}

Rgb Rgb::operator-(const Rgb &other) const
{
    return Rgb(_red-other.red(), _green-other.green(), _blue-other.blue());
}

Rgb Rgb::operator*(const double factor) const
{
    return Rgb(_red*factor, _green*factor, _blue*factor);
}

Rgb Rgb::operator*(const Rgb &other) const
{
    return Rgb(_red*other.red(), _green*other.green(), _blue*other.blue());
}

Rgb &Rgb::operator +=(const Rgb &other)
{
    _red += other.red();
    _green += other.green();
    _blue += other.blue();
    return *this;
}

Rgb &Rgb::operator -=(const Rgb &other)
{
    _red -= other.red();
    _green -= other.green();
    _blue -= other.blue();
    return *this;
}
