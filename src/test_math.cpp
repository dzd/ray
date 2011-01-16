using namespace std;

#include <iostream>
#include <string>

#include "Ray_Math.hpp"
#include "Ray_Color.hpp"

void test_matrix_operators();
void test_vector_rotation();
void test_vector();
void test_matrix3();
void test_color();

void test_vector_reflection();

int main()
{
    test_matrix3();
    test_matrix_operators();
    test_vector_rotation();
    test_vector();
    test_color();
    test_vector_reflection();
    return 0;
}

void test_matrix3()
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
        cout << "m1 inverse is:\n" << m3 << endl;
    else 
        cout << "m1 isn't inversible"<< endl;

    if( m4.inverse(m3))
        cout << "m4 inverse is:\n" << m3  << endl;
    else 
        cout << "m4 isn't inversible"<< endl;
}

void test_matrix_operators()
{
    Matrix3 m1(1,2,3,4,5,6,7,8,9);
    Matrix3 m2(-2,2,-3,-1,1,3,2,0,-1);
    Matrix3 m3(1,0,1,0,1,0,1,0,1);
    Matrix3 m4(-1,2,5,1,2,3,-2,8,10);

    cout << "m1\n" << m1 << endl;
    cout << "m2\n" << m2 << endl;
    cout << "m3\n" << m3 << endl;
    cout << "m4\n" << m4 << endl;

    cout << "m1 - m2\n" << m1-m2 << endl;
    cout << "m1 * 2\n" << m1*2 << endl;
}

void test_vector_rotation()
{
    Vector v(-1 ,-1, 0);
    Vector axis_v(0 ,0, 1);
    float angle = M_PI;

    cout << "Rotate v: " << v << ", by "<< angle<<"°, around axis: "<< axis_v << " = " << v.Rotate(axis_v, angle) << endl;

    Vector normal_v(0,1,0);
    Vector axis2_v = cross(v ,normal_v);
        cout << "Rotate v: " << v << ", by "<< angle<<"°, around axis: "<< axis2_v << " = " << v.Rotate(axis2_v, angle) << endl;
}

void test_vector()
{
    //o: [0,0,1], r: [0.0259306,0.00449191,-0.999654]
    Vector v1(0,0,1);
    Vector v2(0.0259306,0.00449191,-0.999654);

    float dot_f = dot(v1, v2);
    cout << "v1: " <<v1 << "v2: " <<v2<<"dot(v1, v2)" << dot_f << endl;
}

void test_color()
{
    cout << "TEST: COLOR\n";
    Color c1(0,0,0);
    Color c2(240, 125, 13);
    c1 = c2 * 1.2;
    
    c2.Show();
    c1.Show();
}

void test_vector_reflection()
{
    cout << "TEST: VECTOR REFLECTION\n";
    Vector v1(-3,-1,0);
    Vector n(0,2,0);

    Vector v3(v1.Reflection(n));

    cout <<"v1: " << v1 << endl;
    cout <<"n: " << n << endl;
    cout <<"v3(reflection): " << v3 << endl;


}


