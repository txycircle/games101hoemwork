#include "Bounds3.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"


bool Bounds3::IntersectionP(const Ray& _ray)
{
	std::array<int, 3> IsNegDir{ 0,0,0 };
	if (_ray.dir.x >= 0) IsNegDir[0] = 1;
	if (_ray.dir.y >= 0) IsNegDir[1] = 1;
	if (_ray.dir.z >= 0) IsNegDir[2] = 1;

	Vector3f invDir(1.0f / _ray.dir.x, 1.0f / _ray.dir.y, 1.0f / _ray.dir.z);

	float tenterx = (pMin.x - _ray.origin.x) * invDir.x;
	float texitx = (pMax.x - _ray.origin.x) * invDir.x;

	float tentery = (pMin.y - _ray.origin.y) * invDir.y;
	float texity = (pMax.y - _ray.origin.y) * invDir.y;

	float tenterz = (pMin.z - _ray.origin.z) * invDir.z;
	float texitz = (pMax.z - _ray.origin.z) * invDir.z;

	if (IsNegDir[0] == 0)
	{
		float t = tenterx;
		tenterx = texitx;
		texitx = t;
	}
	if (IsNegDir[1] == 0)
	{
		float t = tentery;
		tentery = texity;
		texity = t;
	}
	if (IsNegDir[2] == 0)
	{
		float t = tenterz;
		tenterz = texitz;
		texitz = t;
	}

	float tenter = std::fmax(std::fmax(tenterx, tentery), tenterz);
	float texit = std::fmin(std::fmin(texitx, texity), texitz);

	if (tenter <= texit && texit > 0)
		return true;
	else
		return false;

}


Bounds3 Union(const Bounds3& b1, const Bounds3& b2)
{
	Vector3f pMin, pMax;
	pMin = Vector3f::Min(b1.pMin, b2.pMin);
	pMax = Vector3f::Max(b1.pMax, b2.pMax);
	return Bounds3(pMin, pMax);
}

Bounds3 Union(const Bounds3& b1, const Vector3f v)
{
	Vector3f pMin, pMax;
	pMin = Vector3f::Min(b1.pMin, v);
	pMax = Vector3f::Max(b1.pMax, v);
	return Bounds3(pMin, pMax);
}
