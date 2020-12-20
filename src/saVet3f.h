#if !defined(__SA_VET3F__)
#define __SA_VET3F__

#include <cmath>
#include <cstdio>

#ifndef M_PI
#define M_PI 3.1415926535897932384
#endif

class saVet3f {
public:
    double x, y, z;

    saVet3f();
    saVet3f(double x_, double y_, double z_);

    saVet3f add(const saVet3f& other);
    saVet3f subtract(const saVet3f& other);
    saVet3f mul(double value);
    saVet3f div(double value);
    saVet3f mul(const saVet3f& other);
    saVet3f div(const saVet3f& other);
    double dot(const saVet3f& other);
    saVet3f cross(const saVet3f& other);
    double angle_rad(const saVet3f& other);
    double angle_deg(const saVet3f& other);
    double norm(void);
    double dist(const saVet3f& other);
    saVet3f normalize(void);
    saVet3f scale(double size);
    saVet3f rotate_rad(double angle, int axis);
    saVet3f rotate_deg(double angle, int axis);
    saVet3f operator+(const saVet3f& other);
    saVet3f operator-(const saVet3f& other);
    saVet3f operator*(double value);
    saVet3f operator/(double value);
    saVet3f operator*(const saVet3f& other);
    saVet3f operator/(const saVet3f& other);
    double operator[](int idx);
    void p(void);
};

#endif // __SA_VET3F__
