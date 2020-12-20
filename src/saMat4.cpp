#include "saMat4.h"

saMat4::saMat4()    
{}

saMat4::~saMat4()
{}

void saMat4::set(int32_t i, int32_t j, double value)
{
    (*this)[i][j] = value;    
}

void saMat4::set_row(int32_t i, double a, double b, double c, double d)
{
    (*this)[i][0] = a;
    (*this)[i][1] = b;
    (*this)[i][2] = c;
    (*this)[i][3] = d;
}

void saMat4::set_col(int32_t i, double a, double b, double c, double d)
{
    (*this)[0][i] = a;
    (*this)[1][i] = b;
    (*this)[2][i] = c;
    (*this)[3][i] = d;
}

saMat3 saMat4::redu(int8_t x, int8_t y)
{
    saMat3 result;
    int8_t cont = 0;
    for (int8_t i = 0; i < 4; i++) 
    {
        if (i == x) continue;
        for (int8_t j = 0; j < 4; j++) 
        {
            if (j == y) continue;

            result[cont++] = (*this)[i][j];
        }
    }
    result.transpose();
    return result;
}

saMat4 saMat4::mul(double scalar)
{
    saMat4 result;

    result[0][0] = (*this)[0][0] * scalar;
    result[0][1] = (*this)[0][1] * scalar;
    result[0][2] = (*this)[0][2] * scalar;
    result[0][3] = (*this)[0][3] * scalar;
    result[1][0] = (*this)[1][0] * scalar;
    result[1][1] = (*this)[1][1] * scalar;
    result[1][2] = (*this)[1][2] * scalar;
    result[1][3] = (*this)[1][3] * scalar;
    result[2][0] = (*this)[2][0] * scalar;
    result[2][1] = (*this)[2][1] * scalar;
    result[2][2] = (*this)[2][2] * scalar;
    result[2][3] = (*this)[2][3] * scalar;
    result[3][0] = (*this)[3][0] * scalar;
    result[3][1] = (*this)[3][1] * scalar;
    result[3][2] = (*this)[3][2] * scalar;
    result[3][3] = (*this)[3][3] * scalar;
    
    return result;
}

saMat4 saMat4::operator*(double scalar)
{
    return this->mul(scalar);
}

saMat4 saMat4::mul(const saMat4& other)
{
    saMat4 result;
    saMat4 other_ = other;
    
    for (int8_t i = 0; i < 4; i++)
    {
        for (int8_t j = 0; j < 4; j++)
        {
            for (int8_t k = 0; k < 4; k++)
            {
                result[i][j] += (*this)[i][k] * other_[k][j];
            }
        };
    };

    return result;
}

saMat4 saMat4::add(const saMat4& other)
{
    saMat4 result;

    result[0][0] = (*this)[0][0] + other._mat[0].x;
    result[0][1] = (*this)[0][1] + other._mat[0].y;
    result[0][2] = (*this)[0][2] + other._mat[0].z;
    result[0][3] = (*this)[0][3] + other._mat[0].w;
    result[1][0] = (*this)[1][0] + other._mat[1].x;
    result[1][1] = (*this)[1][1] + other._mat[1].y;
    result[1][2] = (*this)[1][2] + other._mat[1].z;
    result[1][3] = (*this)[1][3] + other._mat[1].w;
    result[2][0] = (*this)[2][0] + other._mat[2].x;
    result[2][1] = (*this)[2][1] + other._mat[2].y;
    result[2][2] = (*this)[2][2] + other._mat[2].z;
    result[2][3] = (*this)[2][3] + other._mat[2].w;
    result[3][0] = (*this)[3][0] + other._mat[3].x;
    result[3][1] = (*this)[3][1] + other._mat[3].y;
    result[3][2] = (*this)[3][2] + other._mat[3].z;
    result[3][3] = (*this)[3][3] + other._mat[3].w;
    
    return result;
}

saMat4 saMat4::operator+(const saMat4& other)
{
    return this->add(other);
}

void saMat4::operator+=(const saMat4& other)
{
    (*this)[0][0] += other._mat[0].x;
    (*this)[0][1] += other._mat[0].y;
    (*this)[0][2] += other._mat[0].z;
    (*this)[0][3] += other._mat[0].w;
    (*this)[1][0] += other._mat[1].x;
    (*this)[1][1] += other._mat[1].y;
    (*this)[1][2] += other._mat[1].z;
    (*this)[1][3] += other._mat[1].w;
    (*this)[2][0] += other._mat[2].x;
    (*this)[2][1] += other._mat[2].y;
    (*this)[2][2] += other._mat[2].z;
    (*this)[2][3] += other._mat[2].w;
    (*this)[3][0] += other._mat[3].x;
    (*this)[3][1] += other._mat[3].y;
    (*this)[3][2] += other._mat[3].z;
    (*this)[3][3] += other._mat[3].w;
}

double saMat4::det()
{
    double det = 0.;

    // iterando em uma linha
    for(int8_t i = 0; i < 4; i++)
    {
        det += pow(-1.0, i) * (*this)[i][0] * this->redu(i,0).det();
    }
    return det;
}

saMat4 saMat4::transpose()
{
    saMat4 result;
    
    for (int8_t i = 0; i < 4; i++) 
    {
        for (int8_t j = 0; j < 4; j++) 
        {
            result[i][j] = (*this)[j][i];
        }
    }
    
    return result;
}

saMat4 saMat4::cof()
{
    saMat4 result;
    for(int8_t i = 0; i < 4; i++) 
    {
        for(int8_t j = 0; j < 4; j++) 
        {
            result[i][j] = pow(-1.0, i + j) * this->redu(i,j).det();
        }
    }
    return result;
}

saMat4 saMat4::inv()
{
    return (*this).cof().transpose().mul(1/this->det());
}

saVet4& saMat4::operator[](const int& index)
{
    switch (index)
    {
        case 0:  return _mat[0];
        case 1:  return _mat[1];
        case 2:  return _mat[2];
        case 3:  return _mat[3];
        default: return (*this)[index%4];
    }
}

void saMat4::p(void) 
{
    printf("matrix4: \n");
    printf("%f, %f, %f, %f\n", _mat[0][0], _mat[0][1], _mat[0][2], _mat[0][3]);
    printf("%f, %f, %f, %f\n", _mat[1][0], _mat[1][1], _mat[1][2], _mat[1][3]);
    printf("%f, %f, %f, %f\n", _mat[2][0], _mat[2][1], _mat[2][2], _mat[2][3]);
    printf("%f, %f, %f, %f\n", _mat[3][0], _mat[3][1], _mat[3][2], _mat[3][3]);
    printf("\n");
}

void saMat4::p(std::string label) 
{
    printf("matrix4: %s\n", label.c_str());
    printf("%f, %f, %f, %f\n", _mat[0][0], _mat[0][1], _mat[0][2], _mat[0][3]);
    printf("%f, %f, %f, %f\n", _mat[1][0], _mat[1][1], _mat[1][2], _mat[1][3]);
    printf("%f, %f, %f, %f\n", _mat[2][0], _mat[2][1], _mat[2][2], _mat[2][3]);
    printf("%f, %f, %f, %f\n", _mat[3][0], _mat[3][1], _mat[3][2], _mat[3][3]);
    printf("\n");
}