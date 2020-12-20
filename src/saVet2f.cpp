#include "saVet2f.h"

saVet2f::saVet2f(): x(0), y(0)
{
}

saVet2f::saVet2f(double x, double y): x(x), y(y)
{
}

saVet2f saVet2f::add(const saVet2f& other) 
{
	saVet2f res;
	res.x = x + other.x;
	res.y = y + other.y;
	return res;
}

saVet2f saVet2f::subtract(const saVet2f& other) 
{
	saVet2f res;
	res.x = x - other.x;
	res.y = y - other.y;
	return res;
}

saVet2f saVet2f::mul(double value) 
{
	saVet2f res;
	res.x = x * value;
	res.y = y * value;
	return res;
}

saVet2f saVet2f::div(double value)
{
	saVet2f res;
	res.x = x / value;
	res.y = y / value;
	return res;
}

saVet2f saVet2f::mul(const saVet2f& other)
{
	saVet2f res;
	res.x = x * other.x;
	res.y = y * other.y;
	return res;
}

saVet2f saVet2f::div(const saVet2f& other)
{
	saVet2f res;
	res.x = x / other.x;
	res.y = y / other.y;
	return res;
}

double saVet2f::dot(const saVet2f& other)
{
	return x*other.x + y*other.y;
}

double saVet2f::norm(void)
{
	return sqrt(this->dot(*this));
}

double saVet2f::angle_rad(const saVet2f& other)
{
	double ang = 0.0;
	saVet2f v2 = other;
	
	// calculo valor do angulo
	ang = acos(this->dot(v2)/this->norm()/v2.norm());

	// ajuste de sinal
	if ((x*other.y - other.x*y) < 0.0) {
		ang = -ang;
	}

	return ang;
}

double saVet2f::angle_deg(const saVet2f& other)
{
	double ang = this->angle_rad(other)*180./M_PI;

	return ang;
}

double saVet2f::dist(const saVet2f& other)
{
	double dist = this->subtract(other).norm();
	return dist;
}

saVet2f saVet2f::normalize(void)
{
	return this->mul(1./this->norm());
}

saVet2f saVet2f::scale(double size)
{
	return this->normalize()*size;
}

saVet2f saVet2f::rotate_rad(double angle)
{
	saVet2f vet = {0.,0.};

	vet.x =  (*this)[0]*cos(angle) + (*this)[1]*sin(angle);
	vet.y = -(*this)[0]*sin(angle) + (*this)[1]*cos(angle);
	
	return vet;
}

saVet2f saVet2f::rotate_deg(double angle)
{
	return this->rotate_rad(angle*M_PI/180.);
}

saVet2f saVet2f::operator+(const saVet2f& other)
{
	return this->add(other);
}

saVet2f saVet2f::operator-(const saVet2f& other)
{
	return this->subtract(other);
}

saVet2f saVet2f::operator*(double value)
{
	return this->mul(value);
}

saVet2f saVet2f::operator/(double value)
{
	return this->div(value);
}

saVet2f saVet2f::operator*(const saVet2f& other)
{
	return this->mul(other);
}

saVet2f saVet2f::operator/(const saVet2f& other)
{
	return this->div(other);
}

double saVet2f::operator[](int idx)
{
	
	switch(idx)
	{
		case 0: return x;
		case 1: return y;
		default: return (*this)[idx%2];
	}
	
}

void saVet2f::p(void)
{
	printf("v: %.2f, %.2f\n", x, y);
}