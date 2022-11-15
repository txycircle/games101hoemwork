#pragma once

#ifndef BVH__HPP
#define BVH__HPP

#include <algorithm>
#include <iostream>
#include <vector>

#include "Bounds3.hpp"


struct BVHBuildNode;

struct Intersection;
struct Ray;
class Object;
class Vector3f;

class BVHAccel
{
public:
	
	BVHAccel(std::vector<Object*> p):root(nullptr),primitives(p)
	{
		if (p.size() == 0) return;
		root = RecursiveBuild(primitives);
		
	}
	BVHBuildNode* RecursiveBuild(std::vector<Object*> p);
	Intersection GetIntersection(const Ray& _ray, BVHBuildNode* node);
	Intersection Intersect(const Ray& _ray);
	
	void Sample(Intersection& pos, float& pdf);
	void GetSample(Intersection& pos, float& pdf, float p, BVHBuildNode* node);
	
	BVHBuildNode* root;
	std::vector<Object*> primitives;
};


struct BVHBuildNode
{
	Bounds3 bounds;
	BVHBuildNode* left;
	BVHBuildNode* right;
	Object* object;
	float area;
public:
	//BVHBuildNode() :bounds(Bounds3()), left(nullptr), right(nullptr), object(nullptr), area(0.0f) {};
	BVHBuildNode();
};
#endif //! BVH__HPP
