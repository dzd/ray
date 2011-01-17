#ifndef _RAY_COLOR_
#define _RAY_COLOR_

#include <iostream>

class Color 
{
protected:
    void Normalize();

public:
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Color();
    Color(unsigned char cr, unsigned char cg, unsigned char cb);
    Color(int ir, int ig, int ib);
    Color(const Color & c);


    void Add   (const Color & c);
    void Minus (const Color & c);
    Color operator*(float coef);
    //void Set(unsigned char r, unsigned char g, unsigned char b);
    void Set(unsigned int r, unsigned int g, unsigned int b);

    void Show();
};

ostream & operator<<(ostream &o, Color & c);
Color operator+(const Color & c1, const Color & c2);


#endif // _RAY_COLOR_
