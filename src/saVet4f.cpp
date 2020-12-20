#include "saVet4f.h"

saVet4::saVet4() 
    : x(0.),y(0.),z(0.),w(0.)
{
}

saVet4::~saVet4() 
{
}

double& saVet4::operator[](int32_t index)
{
    switch (index)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: return (*this)[index%4];
    }
}