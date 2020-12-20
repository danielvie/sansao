/*
 * sansao.h
 *
 *  Created on: 08/12/2014
 *      Author: User
 */

#ifndef SANSAO_H_
#define SANSAO_H_

#ifndef M_PI
#define M_PI 3.1415926535897932384
#endif

#include <cmath>
#include "saMat3.h"
#include "saVet2f.h"
#include "saVet3f.h"

class sansao {
public:
	static double calc_ang_vetores(const struct saVet3f& v1, const struct saVet3f& v2);
     static int minimo(double *x, int tam);
     static double arredonda(double x);
     static double trunca(double x);
     
     static int sinal(double nro);
};

#endif /* SANSAO_H_ */
