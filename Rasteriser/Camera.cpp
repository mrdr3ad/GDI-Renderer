#include "Camera.h"




Camera::Camera()
{
}


Camera::~Camera()
{
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex & position)
{
	//works out the viewing matrix 
	viewingMat = Matrix().XYZRotationMatrix(xRotation, yRotation, zRotation) * Matrix().TranslationMatrix(position.GetX() * -1, position.GetY() * -1 , position.GetZ() * -1);
	_position = position;
}

Vertex Camera::GetPosition()
{
	return _position;
}

void Camera::SetPosition(Vertex &newPosition)
{
	_position = newPosition;
}
