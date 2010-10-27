#ifndef _RAY_COLOR_
#define _RAY_COLOR_

class Color 
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	
	Color() { r = 0; g = 0; b = 0;} 
	Color(unsigned char cr, unsigned char cg, unsigned char cb) {	
                                    r = cr;
                                    g = cg;
                                    b = cb;}

	Color(int ir, int ig, int ib) { r = ir;
                                    g = ig;
                                    b = ib;
                                  }

    Color(const Color & c) { r = c.r;
                             g = c.g;
                             b = c.b;
                           }

	void Show() { cout <<"|"<<(int)r<<"|"<<(int)g<<"|"<<(int)b<<"|"<<endl; }
};


#endif // _RAY_COLOR_
