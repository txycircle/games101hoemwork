#pragma once

#ifndef  OBJECT_HPP
#define  OBJECT_HPP

#include <iostream>

#include "Bounds3.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"

class Object
{
public:
	Object() {}
	virtual ~Object() {}
	
	virtual Intersection GetIntersection(const Ray& ray) = 0;
	virtual bool Intersect(const Ray& ray) = 0;
	virtual void Sample(Intersection& pos, float& pdf) = 0;
	virtual void GetSurfacePropertices() = 0;
	virtual Bounds3 GetBounds() = 0;
	virtual float GetArea()const = 0;
	virtual bool HasEmit() = 0;
};
#endif // ! OBJECT_HPP
