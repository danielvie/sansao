#include "saVet3f.h"

saVet3f::saVet3f()
	:x(0.), y(0.), z(0.)
{
}

saVet3f::saVet3f(double x_, double y_, double z_)
	:x(x_), y(y_), z(z_)
{
}

saVet3f saVet3f::add(const saVet3f& other) 
{
	saVet3f res;
	res.x = x + other.x;
	res.y = y + other.y;
	res.z = z + other.z;
	return res;
}

saVet3f saVet3f::subtract(const saVet3f& other) 
{
	saVet3f res;
	res.x = x - other.x;
	res.y = y - other.y;
	res.z = z - other.z;
	return res;
}

saVet3f saVet3f::mul(double value) 
{
	saVet3f res;
	res.x = x * value;
	res.y = y * value;
	res.z = z * value;
	return res;
}

saVet3f saVet3f::div(double value)
{
	saVet3f res;
	res.x = x / value;
	res.y = y / value;
	res.z = z / value;
	return res;
}

saVet3f saVet3f::mul(const saVet3f& other)
{
	saVet3f res;
	res.x = x * other.x;
	res.y = y * other.y;
	res.z = z * other.z;
	return res;
}

saVet3f saVet3f::div(const saVet3f& other)
{
	saVet3f res;
	res.x = x / other.x;
	res.y = y / other.y;
	res.z = z / other.z;
	return res;
}

double saVet3f::dot(const saVet3f& other)
{
	return x*other.x + y*other.y + z*other.z;
}

saVet3f saVet3f::cross(const saVet3f& other)
{
	saVet3f res;

	res.x = y*other.z - other.y*z;
	res.y = z*other.x - other.z*x;
	res.z = x*other.y - other.x*y;

	return res;
}

double saVet3f::norm(void)
{
	return sqrt(this->dot(*this));
}

double saVet3f::angle_rad(const saVet3f& other)
{
	double ang = 0.0;
	saVet3f v2 = other;
	
	// calculo valor do angulo
	ang = acos(this->dot(v2)/this->norm()/v2.norm());

	// ajuste de sinal
	if (this->cross(v2).z < 0.0) 
	{
		ang = -ang;
	}

	return ang;
}

double saVet3f::angle_deg(const saVet3f& other)
{
	double ang = this->angle_rad(other)*180./M_PI;

	return ang;
}

double saVet3f::dist(const saVet3f& other)
{
	double dist = this->subtract(other).norm();
	return dist;
}

saVet3f saVet3f::normalize(void)
{
	return this->mul(1./this->norm());
}

saVet3f saVet3f::scale(double size)
{
	return this->normalize()*size;
}

saVet3f saVet3f::rotate_rad(double angle, int axis)
{
	// TODO: testar casos de rotacao para validar
	
	saVet3f vet = {0.,0.,0.};

	if (axis == 1)
	{
		vet.x =  (*this)[0];
		vet.y =  (*this)[1]*cos(angle) + (*this)[2]*sin(angle);
		vet.z = -(*this)[1]*sin(angle) + (*this)[2]*cos(angle);
	}
	if (axis == 2)
	{
		vet.x =  (*this)[0]*cos(angle) - (*this)[2]*sin(angle);
		vet.y =  (*this)[1];
		vet.z =  (*this)[0]*sin(angle) + (*this)[2]*cos(angle);
	}
	if (axis == 3)
	{
		vet.x =  (*this)[0]*cos(angle) + (*this)[1]*sin(angle);
		vet.y = -(*this)[0]*sin(angle) + (*this)[1]*cos(angle);
		vet.z =  (*this)[2];
	}

	return vet;
}

saVet3f saVet3f::rotate_deg(double angle, int axis)
{
	return this->rotate_rad(angle*M_PI/180., axis);
}

saVet3f saVet3f::operator+(const saVet3f& other)
{
	return this->add(other);
}

saVet3f saVet3f::operator-(const saVet3f& other)
{
	return this->subtract(other);
}

saVet3f saVet3f::operator*(double value)
{
	return this->mul(value);
}

saVet3f saVet3f::operator/(double value)
{
	return this->div(value);
}

saVet3f saVet3f::operator*(const saVet3f& other)
{
	return this->mul(other);
}

saVet3f saVet3f::operator/(const saVet3f& other)
{
	return this->div(other);
}

double saVet3f::operator[](int idx)
{
	
	switch(idx)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: return (*this)[idx%3];
	}
}

void saVet3f::p(void)
{
	printf("v: %.2f, %.2f, %.2f\n", x, y, z);
}