#include "Model.h"
#include <algorithm>

Model::Model()
{

}


Model::~Model()
{
}

//accessor to get the stored polygons 
std::vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

//accessor to get the stored vertices 
std::vector<Vertex>& Model::GetVerticesconst()
{
	return _transformedVertices;
}

//gets the number of polygons that have been stored
size_t Model::GetPolygonCount()
{
	return _polygons.size();
}

//gets the number of vertices that have been stored in the array
size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

//stores vertices inside the array
void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z));

}

//stores polygons inside the array
void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D (i0, i1, i2));
}

//applies matrix transformations to the vertices 
//transforms each vertice by going through the array at each index 
void Model::TransformLocalVertices(const Matrix & transform)
{
	_transformedVertices.clear();
	for (size_t i = 0; i < _vertices.size(); i++)
	{
		_transformedVertices.push_back(transform * _vertices[i]);
	}
	;
}

//transforms the previously transformed vertices
void Model::TransformTransoformedVertices(const Matrix & transform)
{
	
	for (size_t i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i] = transform * _transformedVertices[i];
	}
}

//dehomogenizes each vertice by dividing each vertice by w which is equal to 1
void Model::DehomogenizeVertexes()
{
	for (size_t i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i].DehomogenizeVertex();
	}
}

//calculates the wether the the camera should show the polygon or not 
void Model::CalculateBackFaces(Camera cam)
{
	Vertex vert0;
	Vertex vert1;
	Vertex vert2;
	Vector3D a, b, normal, eyeVector;
	float result;
	 //retrieves indices and gets the vertices
	for (size_t i = 0; i < _polygons.size(); i++)
	{
		vert0 = _transformedVertices[_polygons[i].GetIndex(0)];
		vert1 = _transformedVertices[_polygons[i].GetIndex(1)];
		vert2 = _transformedVertices[_polygons[i].GetIndex(2)];


		a = vert0 - vert1;
		b = vert0 - vert2;

		normal = Vector3D().CrossProduct(a, b);

		eyeVector = cam.GetPosition() - vert0;

		result = Vector3D().DotProduct(normal, eyeVector);
		
		//checks to see if the dot product of normal and eyeVector is less than 0, if it is it culls the polygon 
		if (result < 0)
		{
			_polygons[i].SetCull(true);
		}
		else
		{
			_polygons[i].SetCull(false); //otherwise it doesnt cull 
		}
	}
}

bool GreaterThanZ(Polygon3D element0, Polygon3D element1)
{
	bool greater = element0.GetAverageZ() > element1.GetAverageZ();
	return greater;
}
	 

void Model::Sort()
{
	Vertex vert0;
	Vertex vert1;
	Vertex vert2;
	float average;

	for (size_t i = 0; i < _polygons.size(); i++)
	{
		vert0 = Vertex(_transformedVertices[_polygons[i].GetIndex(0)]);
		vert1 = Vertex(_transformedVertices[_polygons[i].GetIndex(1)]);
		vert2 = Vertex(_transformedVertices[_polygons[i].GetIndex(2)]);

		average = (vert0.GetZ() + vert1.GetZ() + vert2.GetZ()) / 3;
		_polygons[i].SetAverageZ(average);
	}
	std::sort(_polygons.begin(), _polygons.end(), GreaterThanZ);
}

