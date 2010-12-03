using namespace std;

#include <iostream>
#include <string>

#include "Ray_Math.hpp"

int main()
{
    Matrix3 m1(1,2,3,4,5,6,7,8,9);
    Matrix3 m2(-2,2,-3,-1,1,3,2,0,-1);
    Matrix3 m3;
    Matrix3 m4(-1,2,5,1,2,3,-2,8,10);

    cout << "m1:\n" << m1 << endl;
    cout << "m2:\n" << m2 << endl;
    m3 = m1;
    cout << "m4:\n" << m4 << endl;

    if( m1.inverse(m3) )
        cout << "m1 inverse is: " << m3 << endl;
    else 
        cout << "m1 isn't inversible"<< endl;

    if( m4.inverse(m3))
        cout << "m4 inverse is: " << m3  << endl;
    else 
        cout << "m4 isn't inversible"<< endl;


    return 0;
}
