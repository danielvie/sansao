/*
 * sansao.cpp
 *
 *  Created on: 08/12/2014
 *      Author: User
 */

#include "sansao.h"

double sansao::calc_ang_vetores(const struct saVet3f& v1, const struct saVet3f& v2) 
{
    double ang = 0.0;
	struct saVet3f v1_ = v1;
	struct saVet3f v2_ = v2;
	
	// calculo valor do angulo
	ang = acos(v1_.dot(v2_)/v1_.norm()/v2_.norm());

	// ajuste de sinal
	if (v1_.cross(v2_).z < 0.0) 
	{
		ang = -ang;
	}

	return ang;
}

int sansao::minimo(double *x, int tam)
{
	// encontra o valor minimo do vetor
	double aux = x[0];
	int cont = 0;

	for (int i = 0; i < tam; ++i) 
	{
		if (x[i]<aux)
		{
			aux = x[i];
			cont = i;
		}
	}
	return cont;
}

double sansao::arredonda(double x)
{
	// arredonda X
	double aux = (double)((int)x);
	double ret = (x - aux >= 0.5001)?(aux + 1):(aux);
	
	return ret;
}

double sansao::trunca(double x)
{
	// arredonda X
	double aux = (double)((int)x);
	double ret = aux;
	return ret;
}

int sansao::sinal(double nro)
{
	// encontrando sinal do nro
	// entra o double com o nro e retorna int com o sinal
	int ret = (nro >= 0) ? 1:-1;
	return ret;
}