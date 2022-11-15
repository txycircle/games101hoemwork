#pragma once
#ifndef TRIANGLE_HAPP
#define TRIANGLE_HAPP


#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "object.hpp"
#include "vector.hpp"
#include "Bounds3.hpp"
#include "material.hpp"


class BVHAccel;
struct Intersection;
struct Ray;


class Triangle:public Object
{
public:
	Vector3f v1, v2, v3;
	Vector3f t1, t2, t3;
	Vector3f e1, e2;
	Vector3f normal;
	float area;
	Material* m;
	Bounds3 BoundingBox;
	Triangle(Vector3f _v1, Vector3f _v2, Vector3f _v3, Material* _m);
	float GetArea()const { return area; }
	Intersection GetIntersection(const Ray& ray) ;
	bool Intersect(const Ray& ray) override { return true; };
	void Sample(Intersection& pos, float& pdf) override;
	void GetSurfacePropertices() override {};
	Bounds3 GetBounds() override;
	bool HasEmit() { return m->HasEmission(); }
};


class TriangleMesh :public Object
{
public:
	std::vector<Triangle> Triangles;
	//std::unique_ptr<Vector3f[]> Vertices;
	//std::unique_ptr<unsigned int[]> VertexIndex;
	float TriangleNums;
	Bounds3 BoundingBox;
	Material* m;
	float area;
	BVHAccel* bvh;
	TriangleMesh(const std::string& filename, Material* _m);
	float GetArea()const { return area; }
	Intersection GetIntersection(const Ray& ray) ;
	bool Intersect(const Ray& ray) override { return true; };
	void Sample(Intersection& pos, float& pdf) override;
	void GetSurfacePropertices() override {};
	Bounds3 GetBounds() override;
	bool HasEmit() { return m->HasEmission(); }
};



#endif // !TRIANGLE_HAPP
