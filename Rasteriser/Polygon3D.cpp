#include "Polygon3D.h"



Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	cull = false;
}


Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	cull = false;
}

//sets the polygon thats passed in equal to this polygon
//tells it wether to cull or not 
Polygon3D::Polygon3D(const Polygon3D& p)
{
	for (int i = 0; i < 3; i++)
	{
		_indices[i] = p.GetIndex(i);
	}
	cull = p.GetCull();
	averageZ = p.GetAverageZ();
}

//gets the vertex stored at the index
int Polygon3D::GetIndex(int vertexIndex) const
{
	return _indices[vertexIndex];
}


Polygon3D & Polygon3D::operator=(const Polygon3D & rhs)
{
	if (this != & rhs)
	{
		for (int i = 0; i < 3; i++)
		{
			rhs.GetIndex(i);
		}
		averageZ = rhs.GetAverageZ();
	}
	return *this;
}

//gets the value of cull wether its true or false 
bool Polygon3D::GetCull() const
{
	return cull;
}

//Sets the value
void Polygon3D::SetCull(bool newCull)
{
	cull = newCull;
}

float Polygon3D::GetAverageZ() const
{
	return averageZ;
}

void Polygon3D::SetAverageZ(float newAvg)
{
	averageZ = newAvg;
}

