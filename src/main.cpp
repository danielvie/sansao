#include <iostream>
#include <cmath>

// #include "saVet2f.h"
// #include "saVet3f.h"
// #include "saMat4.h"
// #include "saMat3.h"
#include "saMat.h"

// TESTE DE MATRIZ INVERSA
// A = [1,0,0,1,0,2,1,2,2,1,0,1,2,0,1,4] -> (4,4)
// C = [-4,2,-16,6,-1,1,-2,1,2,0,4,-2,1,-1,4,-1] -> (4,4) -> (4,4)
// I = [-2, -.5, 1, .5, 1, .5, 0, -.5, 8, -1, 2, 2, 3, .5, -1, -.5] -> (4,4)

int main(int argc, char const *argv[]) 
{
	saMat m1(4,4);
	
	m1.set_row(0,  {1, 0, 2, 2});
	m1.set_row(1,  {0, 2, 1, 0});
	m1.set_row(2,  {0, 1, 0, 1});
	m1.set_row(3,  {1, 2, 1, 4});
	
	m1.cof().p("m1.cof()");
	m1.inv().p("m1.inv()");

	return 0;
}