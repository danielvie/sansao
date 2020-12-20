#if !defined(LIBMATRIX__)
#define LIBMATRIX__

#include <vector>

struct matrix {
    int lin;
    int col;
    int numel;
    std::vector<double> data;
};

struct matrix mnew(int lin, int col);
struct matrix mones(int lin, int col);
struct matrix mnew_data(double data[], int lin, int col);
struct matrix mcol_stack(struct matrix A, struct matrix B);
void print(struct matrix A);
struct matrix mcpy(struct matrix A);
struct matrix mscale(struct matrix A, double s);
struct matrix mdotpow(struct matrix A, double p);
struct matrix madd(struct matrix A, struct matrix B);
struct matrix msubtract(struct matrix A, struct matrix B);

struct matrix mtr(struct matrix A);
struct matrix minv(struct matrix A);
struct matrix mmul(struct matrix A, struct matrix B);
double mdet(struct matrix A);
struct matrix mcof(struct matrix A);

struct matrix mredu(struct matrix A, int px, int py);
void mset(struct matrix *A, int i, int j, double value);
double mget(struct matrix A, int i, int j);


#endif // LIBMATRIX__
