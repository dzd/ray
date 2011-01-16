using namespace std;

#include "Ray_Color.hpp"

Color::Color()
{
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(unsigned char cr, unsigned char cg, unsigned char cb)
{
    r = cr;
    g = cg;
    b = cb;
}

Color::Color(int ir, int ig, int ib)
{
    r = ir;
    g = ig;
    b = ib;
}

Color::Color(const Color & c)
{
    r = c.r;
    g = c.g;
    b = c.b;
}

void Color::Add(const Color & c)
{
/*    r = r+c.r;
    g = g+c.g;
    b = b+c.b;*/
    this->Set((unsigned int)(r+c.r), (unsigned int)(g+c.g),(unsigned int)(b+c.b));
//    Normalize();
}
void Color::Minus(const Color & c)
{

    if (r > c.r) { r = r -c.r; }
    else { r = 0; }

    if (g > c.g) { g = g -c.g; }
    else { g = 0; }

    if (b > c.b) { b = b -c.b; }
    else { b = 0; }

    Normalize();
}

Color Color::operator*(float coef)
{
    Color c;
    //cout << "op*|" << (float)r << "|" << (float)g << "|" << (float)b << "| coef: "<< coef <<"\n";
    float rf = (float) this->r * coef;
    float gf = (float) this->g * coef;
    float bf = (float) this->b * coef;
    //cout << "op*|" << rf << "|" << gf << "|" << bf << "|\n";
    
    c.Set((unsigned int)rf, (unsigned int)gf, (unsigned int)bf);

    //c.Show();
    //cout << "op*--\n";
    return c;
}


void Color::Show()
{
    cout <<"|"<<(int)r<<"|"<<(int)g<<"|"<<(int)b<<"|"<<endl;
}


/**
 * truncate color value to values into [0,255]
 */
void Color::Normalize()
{
    if(r > 255)
        r = 255;
    if(r < 0)
        r = 0;

    if(g > 255)
        g = 255;
    if(g < 0)
        g = 0;

    if(b > 255)
        b = 255;
    if(b < 0)
        b = 0;

}

void Color::Set(unsigned int r, unsigned int g, unsigned int b)
{
    //cout << "in set: params: "<< (int)r << ", "<< (int)g << ", "<< (int)b << endl;
    //this->Show();
    
    if(r > 255 )    { this->r = 255; }
    else if (r < 0) { this->r = 0;   }   
    else            { this->r = r;}

    if(g > 255 )    { this->g = 255; }
    else if (g < 0) { this->g = 0;   }   
    else            { this->g = g;}

    if(b > 255 )    { this->b = 255; }
    else if (b < 0) { this->b = 0;   }   
    else            { this->b = b;}
    
    //cout << "out set: ";
    //this->Show();
}


ostream & operator<<(ostream &o, Color & c) { return o << "[" << (int)c.r << "," << (int)c.g << "," << (int)c.b << "]"; }
