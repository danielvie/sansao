#if !defined(__SA_VET3F__)
#define __SA_VET3F__

#include <cmath>
#include <cstdio>

#ifndef M_PI
#define M_PI 3.1415926535897932384
#endif

struct saVet3f {
    double x, y, z;

    struct saVet3f add(const struct saVet3f& other);
    struct saVet3f subtract(const struct saVet3f& other);
    struct saVet3f mul(double value);
    struct saVet3f div(double value);
    struct saVet3f mul(const struct saVet3f& other);
    struct saVet3f div(const struct saVet3f& other);
    double dot(const struct saVet3f& other);
    struct saVet3f cross(const struct saVet3f& other);
    double angle_rad(const struct saVet3f& other);
    double angle_deg(const struct saVet3f& other);
    double norm(void);
    double dist(const struct saVet3f& other);
    struct saVet3f normalize(void);
    struct saVet3f scale(double size);
    struct saVet3f rotate_rad(double angle, int axis);
    struct saVet3f rotate_deg(double angle, int axis);
    struct saVet3f operator+(const struct saVet3f& other);
    struct saVet3f operator-(const struct saVet3f& other);
    struct saVet3f operator*(double value);
    struct saVet3f operator/(double value);
    struct saVet3f operator*(const struct saVet3f& other);
    struct saVet3f operator/(const struct saVet3f& other);
    double operator[](int idx);
    void p(void);
};

#endif // __SA_VET3F__
