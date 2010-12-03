using namespace std;

#include "Ray_Math.hpp"

//----------------------------------------------------------------------------------------------------
/**
 * Matrix3 constructor with 9 floats
 */
Matrix3::Matrix3(float a1, float a2, float a3,float b1,float b2,float b3,float c1,float c2,float c3)
{
    Init();
    array[0]=a1;
    array[1]=a2;
    array[2]=a3;
    array[3]=b1;
    array[4]=b2;
    array[5]=b3;
    array[6]=c1;
    array[7]=c2;
    array[8]=c3;
}
/**
 * Matrix3 default constructor
 */
Matrix3::Matrix3()
{
    Init();
    for (int i = 0; i <9; i++)
        array[i] = 0;
}
/**
 * Copy constructor
 **/
Matrix3::Matrix3(const Matrix3 & m)
{
    Init();
    copy(m);
}

/**
 * Assignation operator
 */
void Matrix3::operator=(const Matrix3 & m)
{
    copy(m);
}

/**
 * Copy function
 */
void Matrix3::copy(const Matrix3 & m)
{
cout << "copy" << endl;
    for (int j = 1; j<4; j++)
    {
        for (int i = 1; i<4; i++)
        {
            setAt(i,j,m.at(i,j));
        }
    }
}

/**
 * Init function
 */
void Matrix3::Init()
{
    a = &array[0];
    b = &array[1];
    c = &array[2];
    d = &array[3];
    e = &array[4];
    f = &array[5];
    g = &array[6];
    h = &array[7];
    i = &array[8];
}

/**
 * Getter function
 *@param i line number
 *@param j row number
 */
float Matrix3::at(int i, int j) const
{
    if(i >= 1 && i < 4 && j >= 1 && j < 4)
    {
        return array[3*(i-1)+j-1];
    }
    return 0;
}

/**
 * Setter function
 *@param i line number
 *@param j row number
 */
void Matrix3::setAt(int i, int j, float value)
{
    if(i >= 1 && i < 4 && j >= 1 && j < 4)
    {
        array[3*(i-1)+j-1] = value;
    }
}

/**
 * Ostream operator
 */
ostream & operator<<(ostream & o, const Matrix3 & m)
{
    return o <<"[[" << m.at(1,1) <<","<< m.at(1,2)<<","<<m.at(1,3)<<"]\n"
             <<" [" << m.at(2,1) <<","<< m.at(2,2)<<","<<m.at(2,3)<<"]\n"
             <<" [" << m.at(3,1) <<","<< m.at(3,2)<<","<<m.at(3,3)<<"]]";
}

/**
 * Returns the determinant of the matrix
 */
float Matrix3::det()
{
    return   (*a) * ((*e)*(*i) - (*h)*(*f))
           - (*b) * ((*d)*(*i) - (*g)*(*f))
           + (*c) * ((*d)*(*h) - (*g)*(*e));
}

bool Matrix3::inverse(Matrix3 & mresult)
{
    float det = this->det();
    //cout << "Determinant is: "<< det << endl;
    
    if (det == 0) { return false; }
    float det_1 = 1/det;
    
    mresult.setAt(1,1, ( det_1 * ((*e)*(*i) - (*h)*(*f))) );
    mresult.setAt(1,2, (-det_1 * ((*b)*(*i) - (*h)*(*c))) );
    mresult.setAt(1,3, ( det_1 * ((*b)*(*f) - (*e)*(*c))) );

    mresult.setAt(2,1, (-det_1 * ((*d)*(*i) - (*g)*(*f))) );
    mresult.setAt(2,2, ( det_1 * ((*a)*(*i) - (*g)*(*c))) );
    mresult.setAt(2,3, (-det_1 * ((*a)*(*f) - (*d)*(*c))) );

    mresult.setAt(3,1, ( det_1 * ((*d)*(*h) - (*g)*(*e))) );
    mresult.setAt(3,2, (-det_1 * ((*a)*(*h) - (*g)*(*b))) );
    mresult.setAt(3,3, ( det_1 * ((*a)*(*e) - (*d)*(*b))) );    

    return true;
}

Vector  operator*(Matrix3 &m, Vector& v)
{
    float vx = v.X();
    float vy = v.Y();
    float vz = v.Z();

    return Vector(m.at(1,1)*vx + m.at(1,2)*vy + m.at(1,3)*vz,
                  m.at(2,1)*vx + m.at(2,2)*vy + m.at(2,3)*vz,
                  m.at(3,1)*vx + m.at(3,2)*vy + m.at(3,3)*vz);
}


//----------------------------------------------------------------------------------------------------

/**
* Operator * for dot product between two vectors
*/
float operator*(Vector& v1, Vector &v2)
{
    return v1.X()*v2.X() + v1.Y()*v2.Y() + v1.Z()*v2.Z();
}


Vector operator*(float f, Vector &v)
{
    return Vector(f*v.X(), f*v.Y(), f*v.Z());
}

Vector operator-(Point & p1, Point & p2)
{
    return Vector(p1.X() - p2.X(),
                    p1.Y() - p2.Y(),
                    p1.Z() - p2.Z());
}

/**
* Cross product
*/
Vector cross(const Vector& v1, const Vector &v2)
{
    return Vector(v1.Y()*v2.Z()-v2.Y()*v1.Z(),
                    v1.Z()*v2.X()-v2.Z()*v1.X(),
                    v1.X()*v2.Y()-v2.X()*v1.Y());
}

/**
 * dot product
 */
float dot(const Vector& v1, const Vector &v2)
{
    return v1.X()*v2.X() + v1.Y()*v2.Y() + v1.Z()*v2.Z();
}

//----------------------------------------------------------------------------------------------------


Vector::Vector(Point p1, Point p2)
{
    Vector v = p2 - p1;
    x = v.X();
    y = v.Y();
    z = v.Z();

}

Vector * Vector::Normed()
{
    float sum = abs(x+y+z);
    return new Vector(x/sum, y/sum, z/sum);
}

//----------------------------------------------------------------------------------------------------
// TODO: suppress this consructor (replaced by the const one)
Ray::Ray(Vector & v, Point & o)
{
    this->v = v.Normed();
    this->o = new Point(o);
}

Ray::Ray(const Vector & v, const Point & o)
{
    Vector vcopy(v);
    this->v = vcopy.Normed();
    this->o = new Point(o);
}

//----------------------------------------------------------------------------------------------------

ostream & operator<<(ostream &o, Point  & p) { return o << "(" << p.X() << "," << p.Y() << "," << p.Z() << ")"; }
ostream & operator<<(ostream &o, Vector & v) { return o << "[" << v.X() << "," << v.Y() << "," << v.Z() << "]"; }
ostream & operator<<(ostream &o, Ray & r)    { return o << "o:" << *(r.GetOrigin()) << ", v:"<< *(r.GetVector());  }

