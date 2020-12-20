#if !defined(__SA_VET2F__)
#define __SA_VET2F__

#include <cmath>
#include <cstdio>

#ifndef M_PI
#define M_PI 3.1415926535897932384
#endif

class saVet2f {
public:
    double x, y;

    saVet2f(void);
    saVet2f(double x, double y);
    saVet2f add(const saVet2f& other);
    saVet2f subtract(const saVet2f& other);
    saVet2f mul(double value);
    saVet2f div(double value);
    saVet2f mul(const saVet2f& other);
    saVet2f div(const saVet2f& other);
    double dot(const saVet2f& other);
    double angle_rad(const saVet2f& other);
    double angle_deg(const saVet2f& other);
    double norm(void);
    double dist(const saVet2f& other);
    saVet2f normalize(void);
    saVet2f scale(double size);
    saVet2f rotate_rad(double angle);
    saVet2f rotate_deg(double angle);
    saVet2f operator+(const saVet2f& other);
    saVet2f operator-(const saVet2f& other);
    saVet2f operator*(double value);
    saVet2f operator/(double value);
    saVet2f operator*(const saVet2f& other);
    saVet2f operator/(const saVet2f& other);
    double operator[](int pos);
    void p(void);
};

#endif // __SA_VET2F__
