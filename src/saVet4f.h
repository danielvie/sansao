#if !defined(__SA_VET4__)
#define __SA_VET4__

#include <iostream>

class saVet4
{
public:
    double x,y,z,w;

    saVet4();
    ~saVet4();

    double& operator[](int32_t index);

};

#endif // __SA_VET4__
