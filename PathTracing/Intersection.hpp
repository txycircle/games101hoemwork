#pragma once

#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "vector.hpp"


class Object;
class Material;
struct Intersection
{
	bool happend;
	Vector3f coord;
	Vector3f normal;
	float dis;
	Object* obj;
	Material* m;
	Vector3f emit;
	Intersection() :happend(false), coord(Vector3f(0.0, 0.0, 0.0)), normal(Vector3f(0.0, 0.0, 0.0)),dis(0),obj(nullptr),m(nullptr),emit(Vector3f(0.0,0.0,0.0)) {}
};
#endif // !INTERSECTION_HPP
