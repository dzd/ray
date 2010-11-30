using namespace std;

#include <iostream>
#include <string>

#include "Ray_Math.hpp"

int main()
{
    Matrix3 m1(1,2,3,4,5,6,7,8,9);
    Matrix3 m2(-2,2,-3,-1,1,3,2,0,-1);
    Matrix3 m3;

    cout << "m1:\n" << m1 << endl;
    cout << "m2:\n" << m2 << endl;
    m3 = m1;
    cout << "m2:\n" << m2 << endl;

    int d1 = m1.det();
    int d2 = m2.det();

    cout << "m1 determinant is: " << d1 << endl;
    cout << "m2 determinant is: " << d2 << endl;

    return 0;
}
