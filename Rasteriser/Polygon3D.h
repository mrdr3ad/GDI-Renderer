#pragma once
#include "Matrix.h"



class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);
	// Accessor to return index of specified vertex
	int GetIndex(int) const;
	Polygon3D& operator= (const Polygon3D &rhs);
	bool GetCull() const;
	void SetCull(bool newCull);
	float GetAverageZ() const;
	void SetAverageZ(float newAvg);


//private:
	int _indices[3];
	bool cull;
	float averageZ;
	//Vector3D _normal = Vector3D().CrossProduct();
};
