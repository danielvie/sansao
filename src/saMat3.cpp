#include "saMat3.h"

saMat3::saMat3(void)
    :a(0.), b(0.), c(0.), d(0.), e(0.), f(0.), g(0.), h(0.), i(0.)
{        
}

saMat3::saMat3( double a_, double b_, double c_, 
                double d_, double e_, double f_, 
                double g_, double h_, double i_)
                :a(a_), b(b_), c(c_), d(d_), e(e_), f(f_), g(g_), h(h_), i(i_)
{     
}

void saMat3::set( double a_, double b_, double c_,
                  double d_, double e_, double f_,
                  double g_, double h_, double i_ )
{
    a = a_;
    b = b_;
    c = c_;
    d = d_;
    e = e_;
    f = f_;
    g = g_;
    h = h_;
    i = i_;
}

void saMat3::set( int32_t i, int32_t j, double value)
{
    (*this)[i+j*3] = value;
}

void saMat3::set_row( int8_t i, double a, double b, double c)
{
    (*this)[i + 0] = a;
    (*this)[i + 3] = b;
    (*this)[i + 6] = c;
}

void saMat3::set_col( int8_t i, double a, double b, double c)
{
    (*this)[i*3 + 0] = a;
    (*this)[i*3 + 1] = b;
    (*this)[i*3 + 2] = c;
}

double& saMat3::get( int32_t i, int32_t j)
{
    return (*this)[i+j*3];
}

double& saMat3::operator[]( const int& index ) 
{
    switch(index) 
    {
        case 0:  return a;
        case 1:  return b;
        case 2:  return c;
        case 3:  return d;
        case 4:  return e;
        case 5:  return f;
        case 6:  return g;
        case 7:  return h;
        case 8:  return i;
        default: return (*this)[index%9];
    }
}

/*
* Transpose:
* This changes the matrix.
* [ a b c ]T    [ a d g ]
* [ d e f ]  =  [ b e h ]
* [ g h i ]     [ c f i ]
*/
void saMat3::transpose()
{
    b += d; d = b - d; b -= d; //swap b and d
    c += g; g = c - g; c -= g; //swap c and g
    f += h; h = f - h; f -= h; //swap f and h
}

saMat3 saMat3::transpose(const saMat3& A)
{
    saMat3 result = A;
    result.transpose();
    return result;
}

double saMat3::det()
{
    double det =  a * e * i
                + b * f * g
                + d * h * c
                - g * e * c
                - d * b * i
                - h * f * a;
    return det;
}

void saMat3::inv() 
{
    float det = this->det();
    saMat3 result;

    //included in these calculations: minor, cofactor (changed signs), transpose (by the order of "="), division through determinant
    result.a = ( e * i - h * f) / det;
    result.b = (-b * i + h * c) / det;
    result.c = ( b * f - e * c) / det;
    result.d = (-d * i + g * f) / det;
    result.e = ( a * i - g * c) / det;
    result.f = (-a * f + d * c) / det;
    result.g = ( d * h - g * e) / det;
    result.h = (-a * h + g * b) / det;
    result.i = ( a * e - d * b) / det;

    *this = result;
}

saMat3 saMat3::operator+(const saMat3& other) 
{
    saMat3 result;
    result.a = a + other.a;
    result.b = b + other.b;
    result.c = c + other.c;
    result.d = d + other.d;
    result.e = e + other.e;
    result.f = f + other.f;
    result.g = g + other.g;
    result.h = h + other.h;
    result.i = i + other.i;

    return result;
}

void saMat3::operator+=(const saMat3& other) 
{
    a += other.a;
    b += other.b;
    c += other.c;
    d += other.d;
    e += other.e;
    f += other.f;
    g += other.g;
    h += other.h;
    i += other.i;
}

saMat3 saMat3::operator-(const saMat3& other) 
{
    saMat3 result;
    result.a = a - other.a;
    result.b = b - other.b;
    result.c = c - other.c;
    result.d = d - other.d;
    result.e = e - other.e;
    result.f = f - other.f;
    result.g = g - other.g;
    result.h = h - other.h;
    result.i = i - other.i;

    return result;
}

void saMat3::operator-=(const saMat3& other) 
{
    a -= other.a;
    b -= other.b;
    c -= other.c;
    d -= other.d;
    e -= other.e;
    f -= other.f;
    g -= other.g;
    h -= other.h;
    i -= other.i;
}

/*
* Multiply a matrix with a scalar
*/
saMat3 saMat3::operator*(double scalar) 
{
    saMat3 result;
    result.a = a * scalar;
    result.b = b * scalar;
    result.c = c * scalar;
    result.d = d * scalar;
    result.e = e * scalar;
    result.f = f * scalar;
    result.g = g * scalar;
    result.h = h * scalar;
    result.i = i * scalar;
    return result;
}

void saMat3::operator*=(double scalar)
{
    a *= scalar;
    b *= scalar;
    c *= scalar;
    d *= scalar;
    e *= scalar;
    f *= scalar;
    g *= scalar;
    h *= scalar;
    i *= scalar;
}

/*
* Divide a matrix with a scalar
*/
saMat3 saMat3::operator/(double scalar) 
{
    saMat3 result;
    result.a = a / scalar;
    result.b = b / scalar;
    result.c = c / scalar;
    result.d = d / scalar;
    result.e = e / scalar;
    result.f = f / scalar;
    result.g = g / scalar;
    result.h = h / scalar;
    result.i = i / scalar;
    return result;
}

void saMat3::operator/=(double scalar)
{
    a /= scalar;
    b /= scalar;
    c /= scalar;
    d /= scalar;
    e /= scalar;
    f /= scalar;
    g /= scalar;
    h /= scalar;
    i /= scalar;
}

/*
* Multiply a 3x3 matrix with a 3x3 matrix
*/
saMat3 saMat3::operator*(const saMat3& other) 
{
    saMat3 result;
    result.a = a * other.a + b * other.d + c * other.g;
    result.b = a * other.b + b * other.e + c * other.h;
    result.c = a * other.c + b * other.f + c * other.i;
    result.d = d * other.a + e * other.d + f * other.g;
    result.e = d * other.b + e * other.e + f * other.h;
    result.f = d * other.c + e * other.f + f * other.i;
    result.g = g * other.a + h * other.d + i * other.g;
    result.h = g * other.b + h * other.e + i * other.h;
    result.i = g * other.c + h * other.f + i * other.i;
    return result;
}


void saMat3::p(void) 
{
    printf("matrix3: \n%f, %f, %f\n%f, %f, %f\n%f, %f, %f\n\n", a,d,g,b,e,h,c,f,i);
}

void saMat3::p(std::string label) 
{
    printf("matrix3: %s \n%f, %f, %f\n%f, %f, %f\n%f, %f, %f\n\n", label.c_str(),a,d,g,b,e,h,c,f,i);
}