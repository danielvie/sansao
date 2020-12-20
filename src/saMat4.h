#if !defined(__SA_MAT4__)
#define __SA_MAT4__

#include <string>
#include <cmath>
#include "saVet4f.h"
#include "saMat3.h"

class saMat4
{
public:
    saVet4 _mat[4];

    saMat4(void);
    
    ~saMat4();

    void set(int32_t i, int32_t j, double value);
    void set_row(int32_t i, double a, double b, double c, double d);
    void set_col(int32_t i, double a, double b, double c, double d);
    
    saMat4 transpose();
    double det();
    saMat4 cof();
    saMat4 inv();
    saMat3 redu(int8_t i, int8_t j);

    saMat4 mul(double scalar);
    saMat4 add(const saMat4& other);
    
    saMat4 mul(const saMat4& other);
    
    saMat4 operator*(double scalar);
    saMat4 operator+(const saMat4& other);
    void operator+=(const saMat4& other);
    saVet4& operator[](const int& idx);
    
    void p();
    void p(std::string label);
};

#endif // __SA_MAT4__
