#pragma once
#include <vector>
#include "Framework.h"
#include "Matrix.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "Model.h"
class Rasteriser : public Framework
{
public:
	void Update(Bitmap &bitmap);
	void Render(Bitmap &bitmap);
	bool Initialise();
	void GeneratePerspectiveMatrix(float d, float aspectRatio);  
	void GenerateViewMatrix(float d, int width, int height);
	void DrawWireFrame(Bitmap &bitmap);
	//void DrawSolidFlat();
	bool _backfaceCullEnabled;
	bool _depthSortingEnabled;

private:
	Matrix _viewMatrix;
	Matrix _perspectiveMatrix;

	size_t _frameCount;

	Model _model;
	Camera _cam;
	Matrix _modelTransfomation;
	Matrix _perspectiveTransfomation;
	Matrix _screenTransfomation;
	float _rotation;
	float _d = 1;

	void DrawString(Bitmap &bitmap, LPCWSTR text, int xpos, int ypos);
};