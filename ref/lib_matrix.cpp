#include <cstdio>
#include <cmath>
#include "lib_matrix.h"

// TODO: rever nomes das funcoes e realocar para 'sansao.cpp'

// TODO: criar testes funcionais para avaliar funcionalidade dos metodos

struct matrix mnew(int lin, int col){
    struct matrix A;
    int i;

    A.lin   = lin;
    A.col   = col;
    A.numel = lin*col;

    for(i = 0; i < A.numel; i++) {
        A.data.push_back(0.0);
    }

    return A;
}

struct matrix mones(int lin, int col){
    struct matrix A;
    int i;

    A.lin   = lin;
    A.col   = col;
    A.numel = lin*col;

    for(i = 0; i < A.numel; i++) {
        A.data.push_back(1.0);
    }

    return A;
}

struct matrix mnew_data(double data[], int lin, int col){
    struct matrix res;
    int numel = lin*col;

    res = mnew(lin, col);

    for (int i = 0; i < numel; i++){
        res.data[i] = data[i];
    }

    return res;
}

struct matrix mcol_stack(struct matrix A, struct matrix B){
    struct matrix res;
    int i,j;

    res = mnew( A.lin, A.col + B.col);
    
    // copiando primeira matriz
    for (i = 0; i < A.lin; i++){
        for (j = 0; j < A.col; j++){
            mset(&res,i,j, mget(A,i,j));
        }
    }
    
    // copiando segunda matriz
    for (i = 0; i < B.lin; i++){
        for (j = 0; j < B.col; j++){
            mset(&res, i, j + A.col, mget(B,i,j));
        }
    }
    
    return res;
}

void print(struct matrix A){
    int i, j;

    printf("\n");
    
    for (i = 0; i < A.lin; i++){
        for (j = 0; j < A.col; j++) {
            printf("%f\t", mget(A,i,j));
        }
        printf("\n");
    }
}

struct matrix mcpy(struct matrix A){
    struct matrix res;

    res = mnew_data(A.data.data(), A.lin, A.col);
    return res;
}

struct matrix mtr(struct matrix A){
    int i, j;
    struct matrix res;

    res = mcpy(A);
    res.lin = A.col;
    res.col = A.lin;

    for (i = 0; i < A.lin; i++){
        for (j = 0; j < A.col; j++) {
            mset(&res, j, i, mget(A, i, j));
        }
    }

    return res;
}


void mset(struct matrix *A, int i, int j, double value){
    A->data[i*A->col + j] = value;
}

double mget(struct matrix A, int i, int j){
    double aux = A.data[i*A.col + j];
    return aux;
}

struct matrix minv(struct matrix A){

    struct matrix C, Adj, inv;
    double det;
    
    C   = mcof(A);

    // calculando matriz adjunta (transposta da matriz cofatora)
    Adj = mtr(C);

    // calculando determinante
    det = mdet(A);

    // calculando inversa [Adj(A)/det(A)]
    inv = mscale(Adj, 1.0/det);
    
    return inv;
}

struct matrix mscale(struct matrix A, double s){
    struct matrix res;
    std::vector<double>::iterator it;
    res = mcpy(A);

    for(it = res.data.begin(); it != res.data.end(); it++ ){
        *it = *it*s;
    }
    return res;
}

struct matrix mdotpow(struct matrix A, double p){
    struct matrix res;
    std::vector<double>::iterator it;
    res = mcpy(A);

    for(it = res.data.begin(); it != res.data.end(); it++ ){
        *it = pow(*it,p);
    }
    return res;
}

struct matrix madd(struct matrix A, struct matrix B){
    struct matrix res;
    int i;

    res = mnew(A.lin, A.col);

    for(i = 0; i < A.numel; i++ ){
        res.data[i] = A.data[i] + B.data[i];
    }
    
    return res;
}

struct matrix msubtract(struct matrix A, struct matrix B){
    struct matrix res;
    int i;

    res = mnew(A.lin, A.col);

    for(i = 0; i < A.numel; i++ ){
        res.data[i] = A.data[i] - B.data[i];
    }

    return res;
}

struct matrix mmul(struct matrix A, struct matrix B){
    int i, j, k;
    struct matrix C, B_t;

    // verificando se a multiplicacao eh possivel
    if (A.col != B.lin) {
        printf("erro! matriz nao multiplicavel!\n");
        return C;
    }
    // criando matrix de saida
    C   = mnew(A.lin, B.col);

    // B_t = mtr(B);

    double sum;
    int cont = 0;
    for(i = 0; i < C.lin; i++){
        for(j = 0; j < C.col; j++){
            sum = 0.0;

            for(k = 0; k < A.col; k++) {
                sum += mget(A,i,k) * mget(B,k,j);
            }

            C.data[cont++] = sum;
        }
    }
    
    return C;
}

double mdet(struct matrix A){
    int i;
    double det;

    det = 0.0;
    if (A.col == 1) {
        return A.data[0];
    }
    
    for(i = 0; i < A.col; i++){
        det += pow(-1.0, i) * A.data[i] * mdet(mredu(A,0,i));
    }

    return det;
}

struct matrix mredu(struct matrix A, int px, int py){
    struct matrix red;
    int i, j, cont;

    red = mnew(A.lin - 1, A.col - 1);
    
    cont = 0;
    for (i = 0; i < A.lin; i++) {
        if (i == px) continue;

        for (j = 0; j < A.col; j++) {
            if (j == py) continue;
            
            red.data[cont++] = mget(A, i, j);
        }
    }

    return mtr(red);
}
struct matrix mcof(struct matrix A){
    // A = [1,0,0,1,0,2,1,2,2,1,0,1,2,0,1,4] -> (4,4)
    // C = [-4,2,-16,6,-1,1,-2,1,2,0,4,-2,1,-1,4,-1] -> (4,4) -> (4,4)
    // I = [-2, .5, 1, .5, 1, .5, 0, -.5, 8, -1, 2, 2, 3, .5, -1, -.5] -> (4,4)

    struct matrix C;
    int i, j;
    double aux;
    
    C = mnew(A.lin, A.col);

    for(i = 0; i < A.lin; i++) {
        for(j = 0; j < A.col; j++) {
            aux = pow(-1.0, i + j) * mdet(mredu(A,i,j));
            mset(&C, i, j, aux);
        }
    }

    return C;
}
