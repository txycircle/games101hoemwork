#pragma once
#ifndef BOUNDS__HPP
#define BOUNDS__HPP

#include <vector>
#include <array>
#include "vector.hpp"


extern struct Ray;


class Bounds3 {
public:
	Bounds3() :pMin(std::numeric_limits<float>::infinity()), pMax(-std::numeric_limits<float>::infinity()) {}
	Bounds3(Vector3f& _pMin,Vector3f& _pMax) :pMin(_pMin), pMax(_pMax) {}
	Bounds3(std::vector<Vector3f>& vs) :pMin(std::numeric_limits<float>::infinity()), pMax(-std::numeric_limits<float>::infinity())
	{
		for (auto v : vs)
		{
			pMin = Vector3f::Min(pMin, v);
			pMax = Vector3f::Max(pMax, v);
		}
	}
	bool IntersectionP(const Ray& _ray);
	int MaxExtent()
	{
		Vector3f dignoal = pMax - pMin;
		if (dignoal.x > dignoal.y && dignoal.x > dignoal.z)
			return 0;
		if (dignoal.y > dignoal.x && dignoal.y > dignoal.z)
			return 1;
		return 2;
	}
	double SurfaceArea();
	Vector3f Centriod()const
	{
		Vector3f dis = (pMax - pMin) / 2;
		return pMin + dis;
	}
	Vector3f pMin, pMax;
	
};
Bounds3 Union(const Bounds3& b1, const Bounds3& b2);

Bounds3 Union(const Bounds3& b1, const Vector3f v);

#endif // !BOUNDS__HPP
