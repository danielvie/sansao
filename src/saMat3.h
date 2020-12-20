#if !defined(__SA_MAT3__)
#define __SA_MAT3__

#include <iostream>
#include <string>

class saMat3
{
public:
    double a,b,c,d,e,f,g,h,i;

    saMat3(void);
    saMat3(double a, double b, double c, 
           double d, double e, double f, 
           double g, double h, double i);
    
    void set( double _a, double _b, double _c,
              double _d, double _e, double _f,
              double _g, double _h, double _i );
    
    void set( int32_t i, int32_t j, double value);
    
    void set_row( int8_t i, double a, double b, double c);
    void set_col( int8_t i, double a, double b, double c);

    double& get( int32_t i, int32_t j);
    
    void transpose();
    saMat3 transpose(const saMat3& A);

    double det();
    void inv();

    saMat3 operator+(const saMat3& other);
    void operator+=(const saMat3& other);

    saMat3 operator-(const saMat3& other);
    void operator-=(const saMat3& other);
    
    saMat3 operator*(double scalar);
    void operator*=(double scalar);
    
    saMat3 operator/(double scalar);
    void operator/=(double scalar);
    
    saMat3 operator*(const saMat3& other);

    double& operator[]( const int& index );

    void p(void);
    void p(std::string label);
};


#endif // __SA_MAT3__
