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
    std::vector<double> *m_data;

    // metodos
    saMat(void);
    saMat(const saMat& other);
    saMat(int32_t lin, int32_t col);
    saMat(int32_t lin, int32_t col, double value);
    saMat(int32_t lin, int32_t col, const std::vector<double>& values);
    ~saMat();

    void init(int32_t lin, int32_t col, double value);

    void set(int32_t i, int32_t j, double value);
    void set(int32_t i, double value);
    double get(int32_t i, int32_t j);
    double get(int32_t i);
    int32_t numel(void);
    
    saMat mul(const saMat& other);
    saMat mul(double value);

    saMat add(const saMat& other);
    saMat subtract(const saMat& other);
    saMat col_stack(const saMat& other);
    saMat transpose(void);
    
    saMat redu(int32_t px, int32_t pj);
    double det(void);
    saMat cof(void);
    saMat inv(void);

    void p(void);
    void pdata(void);
};


#endif // __SA_MAT__
