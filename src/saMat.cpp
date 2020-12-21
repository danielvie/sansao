#include "saMat.h"

saMat::saMat()
    :m_lin(0.), m_col(0.)
{    
}

saMat::saMat(int32_t m_lin_, int32_t m_col_)
    :m_lin(m_lin_), m_col(m_col_)
{
    for (int32_t i = 0; i < this->numel(); i++)
    {
        m_data.push_back(0.);
    }
}

saMat::saMat(int32_t m_lin_, int32_t m_col_, double value)
    :m_lin(m_lin_), m_col(m_col_)
{
    for (int32_t i = 0; i < this->numel(); i++)
    {
        m_data.push_back(value);
    }
}

saMat::~saMat()
{
}

int32_t saMat::numel()
{
    return m_lin*m_col;
}

void saMat::set(int32_t i, int32_t j, double value)
{
    this->m_data[i + j*m_lin] = value;
}

int32_t saMat::set_row(int32_t idx, std::vector<double> row)
{
    if (m_col != (int32_t)row.size())
    {
        printf("numero de elementos nao compativel com set_row\n");
        return 0;
    }

    for ( int32_t i = 0; i < m_col; i++)
    {
        this->set(idx, i, row[i]);
    }

    return 1;
}

int32_t saMat::set_col(int32_t idx, std::vector<double> col)
{
    if (m_lin != (int32_t)col.size())
    {
        printf("numero de elementos nao compativel com set_col\n");
        return 0;
    }

    for ( int32_t i = 0; i < m_lin; i++)
    {
        this->set(i, idx, col[i]);
    }

    return 1;
}

double saMat::get(int32_t i, int32_t j)
{
    return this->m_data[i + j*m_lin];
}

saMat saMat::add(const saMat& other)
{
    saMat result;

    for (int32_t i = 0; i < result.numel(); i++)
    {
        result[i] = this->m_data[i] + other.m_data[i];
    }

    return result;
}

saMat saMat::subtract(const saMat& other)
{
    saMat result;

    for (int32_t i = 0; i < result.numel(); i++)
    {
        result[i] = this->m_data[i] - other.m_data[i];
    }

    return result;
}

saMat saMat::mul(double scalar)
{
    return (*this)*scalar;
}

saMat saMat::divide(double scalar)
{
    return (*this)/scalar;
}

saMat saMat::mul(const saMat& other)
{
    saMat result(m_lin, other.m_col);
    saMat other_ = other;
    double sum=0.;

    for (int i = 0; i < m_lin; i++)
    {
        for (int j = 0; j < other.m_col; j++)
        {
            sum = 0.;
            for (int k = 0; k < m_col; k++)
            {
                sum += (*this).get(i,k) * other_.get(k,j);
            }
            result.set(i,j, sum);
        }
    }
    
    return result;
}

saMat saMat::ipow(double scalar)
{
    saMat result(m_lin, m_col);

    for (int32_t i = 0; i < this->numel(); i++) 
    {
        result[i] = pow((*this)[i], scalar);
    }

    return result;
}


saMat saMat::transpose()
{
    saMat result(m_col, m_lin);

    for (int32_t i = 0; i < m_lin; i++) 
    {
        for (int32_t j = 0; j < m_col; j++) 
        {
            result.set(j,i,  (*this).get(i,j));
        }
    }

    return result;
}

saMat saMat::redu(int32_t i_, int32_t j_)
{
    saMat result(m_lin - 1, m_col - 1);
    int32_t cont = 0;

    for (int32_t i = 0; i < m_lin; i++) 
    {
        if (i == i_) continue;
        for (int32_t j = 0; j < m_col; j++) 
        {
            if (j == j_) continue;

            result[cont++] = this->get(i,j);
        }
    }
    return result.transpose();
}

double saMat::det()
{
    double det = 0.;

    if (this->m_col == 1) 
    {
        return (*this)[0];
    }

    for( int32_t i = 0; i < m_col; i++) 
    {
        det += pow(-1., i) * this->get(0,i) * this->redu(0,i).det();
    }

    return det;
}

saMat saMat::cof()
{
    saMat result(m_lin, m_col);
    
    for (int32_t i = 0; i < m_lin; i++) 
    {
        for (int32_t j = 0; j < m_col; j++) 
        {
            result.set(i,j,  pow(-1., i+j)*this->redu(i,j).det());
        }
    }

    return result;
}

saMat saMat::inv()
{
    saMat result;
    
    // calculando determinante
    double det = this->det();

    // calculando matrix adjunta
    saMat adj = this->cof().transpose();

    // calculando inversa
    result = adj.mul(1./det);

    return result;
}

saMat saMat::col_stack(const saMat& other)
{
    saMat result(m_lin, m_col + other.m_col);

    memcpy(result.m_data.data(), this->m_data.data(), this->numel()*sizeof(double));
    memcpy(result.m_data.data() + this->numel(), other.m_data.data(), (other.m_lin*other.m_col)*sizeof(double));

    return result;
}


double& saMat::operator[](int32_t index)
{
    return this->m_data[index%this->numel()];
}

saMat saMat::operator*(const saMat& other)
{
    return this->mul(other);
}

saMat saMat::operator*(double scalar)
{
    saMat result(m_lin, m_col);
    for (int32_t i = 0; i < (int32_t)this->numel(); i++)
    {
        result[i] = (*this)[i] * scalar;
    }

    return result;
}

void saMat::operator*=(double scalar)
{
    for (int32_t i = 0; i < (int32_t)this->numel(); i++)
    {
        (*this)[i] *= scalar;
    }    
}

saMat saMat::operator/(double scalar)
{
    saMat result;

    for (int32_t i = 0; i < (int32_t)this->numel(); i++)
    {
        result[i] = (*this)[i]/scalar;
    }  

    return result;
}

void saMat::operator/=(double scalar)
{
    for (int32_t i = 0; i < (int32_t)this->numel(); i++)
    {
        (*this)[i] /= scalar;
    }  
}

saMat saMat::operator+(const saMat& other)
{
    return this->add(other);
}

void saMat::operator+=(const saMat& other)
{
    for (int32_t i = 0; i < (int32_t)this->numel(); i++)
    {
        (*this)[i] += other.m_data[i];
    } 
}

saMat saMat::operator-(const saMat& other)
{
    return this->subtract(other);
}

void saMat::operator-=(const saMat& other)
{
    for (int32_t i = 0; i < (int32_t)this->numel(); i++)
    {
        (*this)[i] -= other.m_data[i];
    } 
}

void saMat::p()
{
    printf("matrix(%d,%d):\n", m_lin, m_col);
        
    for (int32_t i = 0; i < m_lin; i++) 
    {
        for (int32_t j = 0; j < m_col; j++) 
        {
            printf("%f, ", this->get(i,j));
        }
        printf("\n");
    }

    printf("\n");
}

void saMat::p(std::string label)
{
    printf("matrix(%d,%d): %s\n", m_lin, m_col, label.c_str());
        
    for (int32_t i = 0; i < m_lin; i++) 
    {
        for (int32_t j = 0; j < m_col; j++) 
        {
            printf("%f, ", this->get(i,j));
        }
        printf("\n");
    }
    printf("\n");
}