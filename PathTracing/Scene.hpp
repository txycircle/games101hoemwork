#pragma once


#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "vector.hpp"

//class Vector3f;
class Object;
class BVHAccel;
struct Ray;
struct Intersection;

class Scene
{
public:
	int width, height;
	double fov;
	Vector3f backgroundcolor;
	BVHAccel* bvh;
	float RussianRoulette;
	std::vector<Object*> objects;

	Scene(int _w, int _h, double _fov= 40, Vector3f background= Vector3f(0.235294, 0.67451, 0.843137)) :width(_w), height(_h), fov(_fov), backgroundcolor(background),bvh(nullptr) { RussianRoulette = 0.8; }
	void Add(Object* obj) { objects.push_back(obj); }
	Vector3f CastRay(const Ray& ray, int depth);
	void BuildBvh();
	void SampleLight(Intersection& pos, float& pdf);
	Intersection intersect(const Ray& ray);
};


#endif //£¡