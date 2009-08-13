#ifndef _RAY_COLOR_
#define _RAY_COLOR_

class Color 
{
public:
	char r;
	char g;
	char b;
	
	Color() { r = (char)0; g = (char)0; b = (char)b;} 
	Color(char r, char g, char b) {	this->r = r;
									this->g = g;
									this->b = b;}

	Color(int r, int g, int b) {	this->r = (char)r;
									this->g = (char)g;
									this->b = (char)b;
	cout << "input: " << r <<" "<< g << " "<< b;
	cout << "result: " << this->r <<","<< this->g << ","<< this->b << endl;
}

	void Show() { cout << (unsigned int)r << ","<< (unsigned int)g << "," << (unsigned int)b <<endl; }

};

#endif // _RAY_COLOR_
