#pragma once
#include "Vertex.h" 
#include "Polygon3D.h"
#include <vector>
#include <iostream>
#include "Matrix.h"
#include "Camera.h"


class Model
{
public:
	Model();
	~Model();
	// Accessor
	
	std::vector<Polygon3D>& GetPolygons();
	std::vector<Vertex>& GetVerticesconst();
	size_t GetPolygonCount() ;
	size_t GetVertexCount() const;
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void TransformLocalVertices(const Matrix &transform);
	void TransformTransoformedVertices(const Matrix &transform);
	void DehomogenizeVertexes();
	void CalculateBackFaces(Camera cam);
	void Sort(void);

//private:
	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _vertices;
	std::vector<Vertex> _transformedVertices;
	Vertex multiplication;
	Polygon3D _polyIndice1, _polyIndice2, _polyIndice3, _vertIndices;
};
