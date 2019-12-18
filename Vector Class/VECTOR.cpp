#include "VECTOR.h"

VECTOR::VECTOR() : x(0.0), y(0.0), z(0.0) {}

VECTOR::VECTOR(long double x, long double y, long double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

long double VECTOR::dotProduct(const VECTOR &v) const
{
     return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

const VECTOR VECTOR::crossProduct(const VECTOR &v) const
{
	return VECTOR((this->y * v.z) - (this->z * v.y),
			(this->z * v.x) - (this->x * v.z),
			(this->x * v.y) - (this->y * v.x));
}

long double VECTOR::length() const
{
    return sqrt((this->x * this->x) + (this->y * this->y)
           + (this->z * this->z));
}

long double VECTOR::angle(const VECTOR &v) const
{
    return acos(this->dotProduct(v) / (this->length() * v.length()));
}

const VECTOR VECTOR::add(const VECTOR &v) const
{
	return VECTOR(this->x + v.x, this->y + v.y, this->z + v.z);
}

const VECTOR VECTOR::subtract(const VECTOR &v) const
{
	return VECTOR(this->x - v.x, this->y - v.y, this->z - v.z);
}

ostream &operator<<(ostream &output, const VECTOR &v)
{
     output << "(" << v.x << ", " << v.y << ", " << v.z << ")";

     return output;
}
