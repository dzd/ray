#ifndef _RAY_IMAGE_
#define _RAY_IMAGE_

#include <string>
#include <iostream>
#include <fstream>

class ImageWriter
{
protected:
	ofstream	output;
	int			width,
				height;

public:
	ImageWriter(string f, int width, int height);

protected:
	virtual void Write() = 0;
	virtual void printHeader() = 0;
 	virtual void printBody() = 0;

};


class BmpWriter : public ImageWriter
{
private:
    int linePadding;
    int empty;
    int headerlenght;
    int bytestotheendheader;
    int numberofbitsperpixel;
    int rawbmpdata;
    int imagesize;
    int nbofcolorplane;
    int pixpermeterH;
    int pixpermeterV;

public:	
	BmpWriter(string f, int width, int height);

protected:
    void Init();
    virtual void Write();
	virtual void printHeader();
	virtual void printBody();
};

#endif // _RAY_IMAGE_
