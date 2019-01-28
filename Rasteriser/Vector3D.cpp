#include "Vector3D.h"

Vector3D::Vector3D()
{
}


Vector3D::~Vector3D()
{
}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

float Vector3D::GetX() const
{
	return _x;
}

void Vector3D::SetX(const float x)
{
	_x = x;
}

float Vector3D::GetY() const
{
	return _y;
}

void Vector3D::SetY(const float y)
{
	_y = y;
}


float Vector3D::GetZ()const
{
	return _z;

}

void Vector3D::SetZ(const float z)
{
	_z = z;
}

//works out the dot product of two vectors and returns a float 
float Vector3D::DotProduct(Vector3D & vector1, Vector3D & vector2)
{
	return _dotProduct = (vector1.GetX() * vector2.GetX()) + (vector1.GetY() * vector2.GetY()) + (vector1.GetZ() * vector2.GetZ());
}

//works out the crossproduct of two vector and returns a vector 
Vector3D Vector3D::CrossProduct(Vector3D & vector1, Vector3D & vector2)
{
	return Vector3D { vector1.GetY() * vector2.GetZ() - vector1.GetZ() * vector2.GetY(),
					vector1.GetZ() * vector2.GetX() - vector1.GetX() * vector2.GetZ(),
					vector1.GetX() * vector2.GetY() - vector1.GetY() * vector2.GetX() };
}



