#include "saVet3f.h"

struct saVet3f saVet3f::add(const struct saVet3f& other) {
	struct saVet3f res;
	res.x = x + other.x;
	res.y = y + other.y;
	res.z = z + other.z;
	return res;
}

struct saVet3f saVet3f::subtract(const struct saVet3f& other) {
	struct saVet3f res;
	res.x = x - other.x;
	res.y = y - other.y;
	res.z = z - other.z;
	return res;
}

struct saVet3f saVet3f::mul(double value) {
	struct saVet3f res;
	res.x = x * value;
	res.y = y * value;
	res.z = z * value;
	return res;
}

struct saVet3f saVet3f::div(double value)
{
	struct saVet3f res;
	res.x = x / value;
	res.y = y / value;
	res.z = z / value;
	return res;
}

struct saVet3f saVet3f::mul(const struct saVet3f& other)
{
	struct saVet3f res;
	res.x = x * other.x;
	res.y = y * other.y;
	res.z = z * other.z;
	return res;
}

struct saVet3f saVet3f::div(const struct saVet3f& other)
{
	struct saVet3f res;
	res.x = x / other.x;
	res.y = y / other.y;
	res.z = z / other.z;
	return res;
}

double saVet3f::dot(const struct saVet3f& other)
{
	return x*other.x + y*other.y + z*other.z;
}

struct saVet3f saVet3f::cross(const struct saVet3f& other)
{
	struct saVet3f res;

	res.x = y*other.z - other.y*z;
	res.y = z*other.x - other.z*x;
	res.z = x*other.y - other.x*y;

	return res;
}

double saVet3f::norm(void)
{
	return sqrt(this->dot(*this));
}

double saVet3f::angle_rad(const struct saVet3f& other)
{
	double ang = 0.0;
	struct saVet3f v2 = other;
	
	// calculo valor do angulo
	ang = acos(this->dot(v2)/this->norm()/v2.norm());

	// ajuste de sinal
	if (this->cross(v2).z < 0.0) {
		ang = -ang;
	}

	return ang;
}

double saVet3f::angle_deg(const struct saVet3f& other)
{
	double ang = this->angle_rad(other)*180./M_PI;

	return ang;
}

double saVet3f::dist(const struct saVet3f& other)
{
	double dist = this->subtract(other).norm();
	return dist;
}

struct saVet3f saVet3f::normalize(void)
{
	return this->mul(1./this->norm());
}

struct saVet3f saVet3f::scale(double size)
{
	return this->normalize()*size;
}

struct saVet3f saVet3f::rotate_rad(double angle, int axis)
{
	// TODO: testar casos de rotacao para validar
	
	struct saVet3f vet = {0.,0.,0.};

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

struct saVet3f saVet3f::rotate_deg(double angle, int axis)
{
	return this->rotate_rad(angle*M_PI/180., axis);
}

struct saVet3f saVet3f::operator+(const struct saVet3f& other)
{
	return this->add(other);
}

struct saVet3f saVet3f::operator-(const struct saVet3f& other)
{
	return this->subtract(other);
}

struct saVet3f saVet3f::operator*(double value)
{
	return this->mul(value);
}

struct saVet3f saVet3f::operator/(double value)
{
	return this->div(value);
}

struct saVet3f saVet3f::operator*(const struct saVet3f& other)
{
	return this->mul(other);
}

struct saVet3f saVet3f::operator/(const struct saVet3f& other)
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