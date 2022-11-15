#pragma once

#ifndef RAY_HPP
#define RAY_HPP
#include "vector.hpp"
struct Ray
{
	Ray(const Vector3f& _ori, const Vector3f& _dir) :origin(_ori), dir(_dir), t(0.0) {}
	Vector3f origin;
	Vector3f dir;
	float t;
	Vector3f operator() (float tvalue)const { return origin + dir * tvalue; }
	//Vector3f operator() (double tvalue) { return origin + dir * tvalue; }
	
};
#endif // !RAY_HPP
