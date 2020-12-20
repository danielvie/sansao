#include <iostream>
#include <cmath>

// #include "saVet2f.h"
// #include "saVet3f.h"
#include "saMat3.h"
// #include "saMat.h"

// std::ostream& operator<<(std::ostream& stream, const Vetor3& v)
// {
// 	stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
// 	return stream;
// }

int main(int argc, char const *argv[]) 
{

	saMat3 m1;

	m1.set(1,3,2,5,6,7,89,9,34);
	
	saMat3 r = m1.transpose(m1);
	m1.p("m1()");
	r.p("r.transpose()");
	
	r.inv();
	r.p("r.inv()");
	
	r += m1;

	r.p("r += m1");

	m1.p("bla");
	for (size_t i = 0; i < 20; i++)
	{
		printf("(%i): %f\n", i, m1[i]);
	}
	

	return 0;
}