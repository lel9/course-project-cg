#ifndef SIZE_H
#define SIZE_H

struct Size
{
    Size() = default;
    Size(const int &x, const int &y) : w(x), h(y) { }
    Size(const Size &s) : w(s.w), h(s.h) { }
    Size(const Size &&s) : w(s.w), h(s.h) { }
    ~Size() = default;

    Size& operator =(const Size &s) { w = s.w; h = s.h; return *this; }
    Size& operator =(const Size &&s) { w = s.w; h = s.h; return *this; }
    int w;
    int h;
};

#endif // SIZE_H
