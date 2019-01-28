#include "Rasteriser.h"


Rasteriser app;
#define DEFAULT_FRAMERATE	30


//updates world and viewing transformations each time the window updates
void Rasteriser::Update(Bitmap &bitmap)
{
	_modelTransfomation = _modelTransfomation.YRotationMatrix(_rotation+=0.01f);
	GeneratePerspectiveMatrix((float)_d,bitmap.GetWidth()/(float)bitmap.GetHeight());
	GenerateViewMatrix(_d,bitmap.GetWidth(),bitmap.GetHeight());
}

//renders the model and sets up the window
void Rasteriser::Render(Bitmap &bitmap)
{
	_frameCount++;

	if (_frameCount == DEFAULT_FRAMERATE * 5)
	{
		_backfaceCullEnabled = !_backfaceCullEnabled;
	}

	if (_frameCount == DEFAULT_FRAMERATE * 10)
	{
		_backfaceCullEnabled = !_backfaceCullEnabled;
		_depthSortingEnabled = !_depthSortingEnabled;
	}

	if (_frameCount == DEFAULT_FRAMERATE * 15)
	{
		_backfaceCullEnabled = true;
		_depthSortingEnabled = true;
		_frameCount = 0;
	}

	// Clear the window to black
	bitmap.Clear(RGB(200, 200, 200));

	_model.TransformLocalVertices(_modelTransfomation);

	if (_backfaceCullEnabled)
		_model.CalculateBackFaces(_cam);

	_model.TransformTransoformedVertices((_cam.viewingMat));

	if (_depthSortingEnabled)
		_model.Sort();

	_model.TransformTransoformedVertices((_perspectiveMatrix));
	_model.DehomogenizeVertexes();
	_model.TransformTransoformedVertices(_viewMatrix);
	DrawWireFrame(bitmap);
	DrawString(bitmap, L"Hello World", 10, 10);

	if (_model.GetPolygonCount() > 0)
		DrawString(bitmap, L"Rendering WireFrame", 10, 10);

	if (_backfaceCullEnabled)
		DrawString(bitmap, L"Bacfaces Culled", 10, 40);

	if (_depthSortingEnabled)
		DrawString(bitmap, L"Depths Sorted", 10, 78);
}


void Rasteriser::DrawString(Bitmap &bitmap, LPCWSTR text, int xpos, int ypos)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	hFont = hFont = CreateFont(38, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("MyFont"));

	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		TextOut(hdc, xpos, ypos, text, wcslen(text));

		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}

bool Rasteriser::Initialise()
{
	//loads a md2 file from a a location
	//"C:\\Users\\byvue\\Desktop\\cube.md2"
	if (!MD2Loader::LoadModel(".\\model.md2", _model,&Model::AddPolygon,&Model::AddVertex))
	{
		return false; 
	}

	_modelTransfomation = Matrix().IdentityMatrix();
	//sets the values for the camera 
	_cam = Camera(0, 0, 0, Vertex(0, 0, -50)) ;

	return true;
}

//creates the perspective matrix
void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	
	_perspectiveMatrix = Matrix{ d / aspectRatio,0,0,0,
			0,d,0,0,
			0,0,d,0,
			0,0,1,0 };
}

//creates the viewing matrix 
void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	
	_viewMatrix = Matrix{ (float)width / 2,0,0,(float)width / 2,
			0, (float)-height / 2, 0,(float)height / 2,
			0,0,d / 2,d / 2,
			0,0,0,1 };
}

//draws the wire frame using polygons 
//gets the dc from bitmap 
void Rasteriser::DrawWireFrame(Bitmap & bitmap)
{
	Vertex vert1;
	Vertex vert2;
	Vertex vert3;
	
	//goes through all the polygons and gets the co-ordinates from each stored index 
	for (size_t i = 0; i < _model.GetPolygonCount(); i++)
	{
	    Polygon3D _polygon = _model.GetPolygons()[i];

		if ((!_polygon.GetCull() && _backfaceCullEnabled) || !_backfaceCullEnabled)
		{
		vert1 = _model.GetVerticesconst()[_polygon.GetIndex(0)];
		vert2 = _model.GetVerticesconst()[_polygon.GetIndex(1)];
		vert3 = _model.GetVerticesconst()[_polygon.GetIndex(2)];
		MoveToEx(bitmap.GetDC(), (int)vert1.GetX(), (int)vert1.GetY(), NULL);
		LineTo(bitmap.GetDC(), (int)vert2.GetX(), (int)vert2.GetY());
		LineTo(bitmap.GetDC(), (int)vert3.GetX(), (int)vert3.GetY());
		LineTo(bitmap.GetDC(), (int)vert1.GetX(), (int)vert1.GetY());
		}


	}
}



