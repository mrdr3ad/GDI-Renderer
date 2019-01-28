#pragma once
#include "Vertex.h"
#include "Matrix.h"

class Camera
{
public:
	Camera();
	~Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	Matrix viewingMat;
	//accessors for the cameras position 
	Vertex GetPosition();
	void SetPosition(Vertex &newPosition);
	

private:
	Vertex _position;

};

