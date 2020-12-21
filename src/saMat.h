#if !defined(__SA_MAT__)
#define __SA_MAT__

#include <iostream>
#include <vector>
#include <cmath>

class saMat
{
public:

    // propriedades
    int32_t m_lin;
    int32_t m_col;
    std::vector<double> m_data;

    // metodos
    saMat();
    saMat(int32_t m_lin, int32_t m_col);
    saMat(int32_t m_lin, int32_t m_col, double value);
    ~saMat();

    void set(int32_t i, int32_t j, double value);
    int32_t set_row(int32_t idx, std::vector<double> row);
    int32_t set_col(int32_t idx, std::vector<double> col);

    double get(int32_t i, int32_t j);

    int32_t numel(void);

    saMat add(const saMat& other);
    saMat subtract(const saMat& other);
    saMat mul(double scalar);
    saMat divide(double scalar);
    saMat mul(const saMat& other);

    saMat transpose();
    saMat redu(int32_t i, int32_t j);
    double det();
    saMat cof();
    saMat inv();
    
    double& operator[](int32_t index);
    
    saMat operator*(double scalar);
    void operator*=(double scalar);
    saMat operator*(const saMat& other);
    
    saMat operator/(double scalar);
    void operator/=(double scalar);

    saMat operator+(const saMat& other);
    void operator+=(const saMat& other);
    
    saMat operator-(const saMat& other);
    void operator-=(const saMat& other);

    void p(void);
    void p(std::string label);
};


#endif // __SA_MAT__
