#include <iostream>
#include <cmath>

// #include "saVet2f.h"
#include "saVet3f.h"
#include "saMat4.h"
#include "saMat3.h"
// #include "saMat.h"

// std::ostream& operator<<(std::ostream& stream, const Vetor3& v)
// {
// 	stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
// 	return stream;
// }

int main(int argc, char const *argv[]) 
{

	saMat4 m1;

	int cont = 0;
	for (int8_t i = 0; i < 4; i++) 
    {
        for (int8_t j = 0; j < 4; j++) 
        {
            m1[j][i] = (double)(cont++);
        }
    }

	m1.set_row(0,  1,0,2,2);
	m1.set_row(1,  0,2,1,0);
	m1.set_row(2,  0,1,0,1);
	m1.set_row(3,  1,2,1,4);

	saMat3 m2;

	m2.set_row(0,  1,2,3);
	m2.set_row(1,  4,5,6);
	m2.set_row(2,  7,8,9);

	m2.p("m2");

	saVet3f v1;

	

	return 0;
}