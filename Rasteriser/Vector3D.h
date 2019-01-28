#pragma once

class Vector3D
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();
	//accessors for to get and set the values of xyz
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ()const;
	void SetZ(const float z);
	//methods to work out the dot and cross product of vectors 
	float DotProduct(Vector3D &vector1, Vector3D &vector2);
	Vector3D CrossProduct(Vector3D &vector1, Vector3D &vector2);
	

	//Polygon3D GetIndices(int i1,int i2, int i3);
	//Vertex GetVertex();


private:

	float _x;
	float _y;
	float _z;
	float _dotProduct;
	
};

