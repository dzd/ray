using namespace std;

#include <iostream>
#include <string>

#include "Ray_Math.hpp"

int main()
{
    Matrix3 m1(1,2,3,4,5,6,7,8,9);
    Matrix3 m2;


    cout << "m1:\n" << m1 << endl;
    cout << "m2:\n" << m2 << endl;
    m2 = m1;
    cout << "m2:\n" << m2 << endl;

    return 0;
}
