using namespace std;

#include "Ray_Image.hpp"

/**
* Base class for image writer...
*/
ImageWriter::ImageWriter(string f, int width, int height)
{
	output.open(f.c_str(), ios::binary | ios::out);
	this->width = width;
	this->height = height;
}

/**
* BmpWriter: base class for output to image file
*/
BmpWriter::BmpWriter(string f, int width, int height)
		 : ImageWriter(f, width, height)
{
	if (output.is_open())
	{
        Write();
		output.close();
	}
	else
		cout << "Error occurred while opening output file: "<< f<< endl;
}

/**
 * init method
 */
void BmpWriter::Init()
{
    empty = 0;
    headerlenght = 54;
    bytestotheendheader = 40;
    numberofbitsperpixel = 24;
    linePadding = (32 - (numberofbitsperpixel * width % 32)) % 32;
    cout << "line padding: " << linePadding << endl;
    rawbmpdata =  (height * (numberofbitsperpixel * width + linePadding)) / 8;
    cout << "raw bmp data: " << rawbmpdata << endl;
    imagesize = headerlenght + rawbmpdata ;
    cout << "image size: " << imagesize << endl;
    nbofcolorplane = 1;
    pixpermeterH = 2835;
    pixpermeterV = 2835;
}

/**
* Main method 
*/
void BmpWriter::Write()
{
    Init();
	printHeader();
	printBody();
}

void BmpWriter::printHeader()
{
/*
2	42 4D		 "BM"	Magic Number (unsigned integer 66, 77)
4	46 00 00 00	 70 Bytes	Size of the BMP file
2	00 00		 Unused	Application Specific
2	00 00		 Unused	Application Specific
4	36 00 00 00	 54 bytes	The offset where the bitmap data (pixels) can be found.
4	28 00 00 00	 40 bytes	The number of bytes in the header (from this point).
4	02 00 00 00	 2 pixels	The width of the bitmap in pixels
4	02 00 00 00	 2 pixels	The height of the bitmap in pixels
2	01 00		 1 plane	Number of color planes being used.
2	18 00		 24 bits	The number of bits/pixel.
4	00 00 00 00	 0	BI_RGB, No compression used
4	10 00 00 00	 16 bytes	The size of the raw BMP data (after this header)
4	13 0B 00 00	 2,835 pixels/meter	The horizontal resolution of the image
4	13 0B 00 00	 2,835 pixels/meter	The vertical resolution of the image
4	00 00 00 00	 0 colors	Number of colors in the palette
4	00 00 00 00	 0 important colors	Means all colors are important */

  output.write("BM", 2);
  output.write((char*)&imagesize, 4);
  output.write((char*)&empty, 2);
  output.write((char*)&empty, 2);
  output.write((char*)&headerlenght, 4);
  output.write((char*)&bytestotheendheader, 4);
  output.write((char*)&width, 4);
  output.write((char*)&height, 4);
  output.write((char*)&nbofcolorplane, 2);
  output.write((char*)&numberofbitsperpixel, 2);
  output.write((char*)&empty, 4);
  output.write((char*)&rawbmpdata, 4);
  output.write((char*)&pixpermeterH, 4);
  output.write((char*)&pixpermeterV, 4);
  output.write((char*)&empty, 4);
  output.write((char*)&empty, 4);

}

void BmpWriter::printBody()
{
    unsigned int r,g,b;
    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            r = i*i;
            g = j*j;
            b = 255;
            //cout <<"r"<< r <<"g"<< g <<"b"<< b;
            output << (unsigned char)r << (unsigned char)g << (unsigned char)b;

        }
        for(int i = 0; i < linePadding; i++)
        { output << (unsigned char)0; }
    }
}

