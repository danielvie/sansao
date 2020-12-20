#include "saMat.h"

// TODO: concertar problema de memoria, caso de erro:
// saMat m1(2,2,{10., 12, 1, 4});
// m1.p();
// saMat r = m1.mul(1./4);
// r.p();
// r = m1.mul(1./4);
// r.p();

    saMat::saMat(void)
        :m_lin(0), m_col(0)
    {
        printf("===============================\n");
        printf("saMat::saMat(void)\n");
        printf("===============================\n");
        m_data = new std::vector<double>;
    }
    
    saMat::saMat(const saMat& other)
        :m_lin(other.m_lin), m_col(other.m_col)
    {
        printf("===============================\n");
        printf("Copied! saMat::saMat(other)\n");
        printf("===============================\n");
        
        m_data = new std::vector<double>(this->numel(), 0.);

        memcpy(m_data->data(), other.m_data->data(), this->numel()*sizeof(double));

    }
    
    saMat::saMat(int32_t lin, int32_t col)
        :m_lin(lin), m_col(col)
    {
        printf("===============================\n");
        printf("Created! saMat::saMat(lin, col)\n");
        printf("===============================\n");

        m_data = new std::vector<double>(this->numel(), 0.);
    }
    
    saMat::saMat(int32_t lin, int32_t col, double value)        
        :m_lin(lin), m_col(col)
    {
        printf("===============================\n");
        printf("Created! saMat::saMat(lin, col, value)\n");
        printf("===============================\n");

        m_data = new std::vector<double>(this->numel(), value);
    }
    
    saMat::saMat(int32_t lin, int32_t col, const std::vector<double>& values)        
        :m_lin(lin), m_col(col)
    {
        printf("===============================\n");
        printf("Created! saMat::saMat(lin, col, values)\n");
        printf("===============================\n");

        if (this->numel() != (int32_t)values.size())
        {
            printf("numero de elementos nao compativel com linhas e colunas!\n");
            m_data = new std::vector<double>(1, 0.);
            m_lin  = 1;
            m_col  = 1;

            return;
        }

        m_data = new std::vector<double>(this->numel(), 0.);
        for (int32_t i = 0; i < this->numel(); i++)
        {
            this->set(i, values[i]);
        }
        
    }
    
    saMat::~saMat()
    {
        delete m_data;
    }


    void saMat::init(int32_t lin, int32_t col, double value)
    {
        m_lin = lin;
        m_col = col;
        
        delete m_data;
        m_data = new std::vector<double>(this->numel(), value);
    }
    
    double saMat::get(int32_t i, int32_t j)
    {
        return (*m_data)[i + j*m_lin];
    }
    
    double saMat::get(int32_t i)
    {
        return (*m_data)[i];
    }
    
    void saMat::set(int32_t i, int32_t j, double value)
    {
        (*m_data)[i + j*m_lin] = value;
    }
    
    void saMat::set(int32_t i, double value)
    {
        (*m_data)[i] = value;
    }
    
    int32_t saMat::numel(void)
    {
        return m_lin*m_col;
    }

    saMat saMat::mul(const saMat& other)
    {
        int32_t i, j, k;

        // verificando se a multiplicacao eh possivel
        if (m_col != other.m_lin)
        {
            printf("erro! matriz nao multiplicavel!\n");
            saMat mat(1, 1);
            return mat;
        }

        saMat mat(m_lin, other.m_col);
        saMat other_ = other;

        double sum;
        for (i = 0; i < m_lin; i++)
        {
            for (j = 0; j < m_col; j++)
            {
                sum = 0.0;
                for (k = 0; k < m_col; k++)
                {
                    sum += this->get(i,k) * other_.get(k,j);
                }
                mat.set(i,j,sum);
            }
        }

        return mat;
    }

    saMat saMat::mul(double value)
    {
        saMat mat(*this);

        printf("teste copia\n");
        this->p();
        mat.p();
        printf("fim teste copia\n");
        for (int32_t i = 0; i < this->numel(); i++)
        {
            mat.set(i, this->get(i)*value);
        }
        
        return mat;
    }

    saMat saMat::add(const saMat& other)
    {
        
        // verificando se a soma eh possivel
        if ((m_col != other.m_col) || (m_lin != other.m_lin))
        {
            printf("erro! matriz nao multiplicavel!\n");
            saMat mat(1, 1);
            return mat;
        }

        saMat mat(m_lin, m_col);
        for(int32_t i = 0; i < this->numel(); i++)
        {
            (*mat.m_data)[i] = (*m_data)[i] + (*other.m_data)[i];
        }

        return mat;
    }
    
    saMat saMat::subtract(const saMat& other)
    {
        
        // verificando se a soma eh possivel
        if ((m_col != other.m_col) || (m_lin != other.m_lin))
        {
            printf("erro! matriz nao compativel subtracao!\n");
            saMat mat(1, 1);
            return mat;
        }

        saMat mat(m_lin, m_col);
        for(int32_t i = 0; i < this->numel(); i++)
        {
            (*mat.m_data)[i] = (*m_data)[i] - (*other.m_data)[i];
        }

        return mat;
    }
    
    saMat saMat::col_stack(const saMat& other)
    {
        
        // verificando se a col_stack eh possivel
        if (m_lin != other.m_lin)
        {
            printf("erro! numero de linhas nao compativeis!\n");
            saMat mat(1, 1);
            return mat;
        }

        saMat mat(m_lin, m_col + other.m_col); 
        saMat other_ = other;
        // copiando primeira matriz
        memcpy(mat.m_data->data(), m_data->data(), this->numel()*sizeof(double));
        
        // copiando segunda matriz
        memcpy(mat.m_data->data() + other_.numel(), other.m_data->data(), this->numel()*sizeof(double));

        return mat;
    }

    saMat saMat::transpose(void)
    {
        
        saMat mat(m_col, m_lin);
        
        for (int32_t i = 0; i < m_lin; i++)
        {
            for (int32_t j = 0; j < m_lin; j++)
            {
                mat.set(j,i,this->get(i,j));
            }
        }

        return mat;
    }

    saMat saMat::redu(int32_t px, int32_t py)
    {
        saMat mat(m_col-1,m_lin-1);
        int32_t cont = 0;    
        for (int32_t i = 0; i < m_lin; i++) 
        {
            if (px == i) continue;
            for (int32_t j = 0; j < m_col; j++) 
            {
                if (py == j) continue;
                mat.set(cont++, this->get(i,j));
            }
        }

        return mat.transpose();

    }

    double saMat::det(void)
    {
        double det;

        if(m_col == 1)
        {
            return this->get(0);
        }

        for (int32_t i = 0; i < m_col; i++)
        {
            det += pow(-1.0, i) * this->get(0,i) * this->redu(0,i).det();
        }
        
        return det;
    }

    saMat saMat::cof(void)
    {
        saMat mat(m_lin, m_col);
        double aux;

        for (int32_t i = 0; i < m_lin; i++) 
        {
            for (int32_t j = 0; j < m_col; j++) 
            {
                aux = pow(-1.0, i + j) * this->redu(i,j).det();
                this->set(i,j,aux);
            }
        }

        return mat;
    }
    
    saMat saMat::inv(void)
    {
        
        saMat mat;

        // verificando se a matriz eh quadrada
        if (m_lin != m_col)
        {
            printf("erro! numero de linhas diferentes do numero de columas!\n");
            return mat;
        }

        double det = this->det();
        
        // verificando se a determinante eh diferente de 0
        if (fabs(det < 1e-15))
        {
            printf("erro! det(matriz) ~== 0.0!\n");
            return mat;
        }

        this->mul(1/det).p();
        mat = this->mul(1/det);

        return mat;
    }


    void saMat::p(void) 
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

    void saMat::pdata(void) 
    {
        printf("matrix(%d,%d).m_data:\n", m_lin, m_col);
        
        for(int32_t i = 0; i < this->numel(); i++) 
        {
            printf("%f, ", (*m_data)[i]);            
        }
        printf("\n\n");

    }