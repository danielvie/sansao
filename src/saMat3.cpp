#include "saMat3.h"

    saMat3::saMat3(void)
        :a(0.), b(0.), c(0.), d(0.), e(0.), f(0.), g(0.), h(0.), i(0.)
    {        
    }
    
    saMat3::saMat3( double a, double b, double c, 
            double d, double e, double f, 
            double g, double h, double i)
            :a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i)
    {     
    }

    void saMat3::set( double _a, double _b, double _c,
                      double _d, double _e, double _f,
                      double _g, double _h, double _i )
    {
        a = _a;
        b = _b;
        c = _c;
        d = _d;
        e = _e;
        f = _f;
        g = _g;
        h = _h;
        i = _i;
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

    void saMat3::set( int32_t i, int32_t j, double value)
    {
        (*this)[i+j*3] = value;
    }
    
    double& saMat3::get( int32_t i, int32_t j)
    {
        return (*this)[i+j*3];
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
        saMat3 r = A;
        r.transpose();
        return r;
    }
    
    double saMat3::det()
    {
        double det = a * e * i
                    + b * f * g
                    + d * h * c
                    - g * e * c
                    - d * b * i
                    - h * f * a;
	    return det;
    }

    void saMat3::inv() {
        float det = this->det();
        saMat3 B;

        //included in these calculations: minor, cofactor (changed signs), transpose (by the order of "="), division through determinant
        B.a = ( e * i - h * f) / det;
        B.b = (-b * i + h * c) / det;
        B.c = ( b * f - e * c) / det;
        B.d = (-d * i + g * f) / det;
        B.e = ( a * i - g * c) / det;
        B.f = (-a * f + d * c) / det;
        B.g = ( d * h - g * e) / det;
        B.h = (-a * h + g * b) / det;
        B.i = ( a * e - d * b) / det;

        *this = B;
    }
    
    saMat3 saMat3::operator+(const saMat3& other) {
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
    
    void saMat3::operator+=(const saMat3& other) {
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

    saMat3 saMat3::operator-(const saMat3& other) {
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
    saMat3 saMat3::operator*(const saMat3& other) {
        saMat3 R;
        R.a = a * other.a + b * other.d + c * other.g;
        R.b = a * other.b + b * other.e + c * other.h;
        R.c = a * other.c + b * other.f + c * other.i;
        R.d = d * other.a + e * other.d + f * other.g;
        R.e = d * other.b + e * other.e + f * other.h;
        R.f = d * other.c + e * other.f + f * other.i;
        R.g = g * other.a + h * other.d + i * other.g;
        R.h = g * other.b + h * other.e + i * other.h;
        R.i = g * other.c + h * other.f + i * other.i;
        return R;
    }


    void saMat3::p(void) 
    {
        printf("matrix3: \n%f, %f, %f\n%f, %f, %f\n%f, %f, %f\n\n", a,d,g,b,e,h,c,f,i);
    }
    
    void saMat3::p(std::string label) 
    {
        printf("matrix3(%s): \n%f, %f, %f\n%f, %f, %f\n%f, %f, %f\n\n", label.c_str(),a,d,g,b,e,h,c,f,i);
    }


