#ifndef MATERIAL_H
#define MATERIAL_H

#include "rgb.h"

class Material
{
public:
    Material() : _Ns(0), _Ni(0), _d(0), _illum(0) { }
    ~Material() = default;

    void setNs(float Ns) { _Ns = Ns; }
    float Ns() const { return _Ns; }

    void setKa(Rgb Ka) { _Ka = Ka; }
    Rgb Ka() const { return _Ka; }

    void setKd(Rgb Kd) { _Kd = Kd; }
    Rgb Kd() const { return _Kd; }

    void setKs(Rgb Ks) { _Ks = Ks; }
    Rgb Ks() const { return _Ks; }

    void setKe(Rgb Ke) { _Ke = Ke; }
    Rgb Ke() const { return _Ke; }

    void setNi(float Ni) { _Ni = Ni; }
    float Ni() const { return _Ni; }

    void setD(float d) { _d = d; }
    float d() const { return _d; }

    void setIllum(int illum) { _illum = illum; }
    int illum() const { return _illum; }

private:
    float _Ns;
    Rgb _Ka;
    Rgb _Kd;
    Rgb _Ks;
    Rgb _Ke;
    float _Ni;
    float _d;
    int _illum;
};

#endif // MATERIAL_H
