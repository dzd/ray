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

    void Show();
};

ostream & operator<<(ostream &o, Color & c);


#endif // _RAY_COLOR_
