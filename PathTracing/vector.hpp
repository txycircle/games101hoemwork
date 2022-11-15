


#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <fstream>


class Vector3f
{
public:
	Vector3f() :x(0.0), y(0.0), z(0.0) {}
	Vector3f(float _val) :x(_val), y(_val), z(_val) {}
	Vector3f(float xx, float yy, float zz) :x(xx), y(yy), z(zz) {}

	Vector3f operator *(const float& r)const { return Vector3f(x*r,y*r,z*r); }
	Vector3f operator /(const float& r)const { return Vector3f(x/r,y/r,z/r); }
	Vector3f operator +(const float& r)const { return Vector3f(x+r,y+r,z+r); }
	
	Vector3f operator * (const Vector3f& v)const { return Vector3f(v.x * x , v.y * y , v.z * z); }
	Vector3f operator + (const Vector3f& v)const { return Vector3f(v.x + x , v.y + y , v.z + z); }
	Vector3f operator - (const Vector3f& v)const { return Vector3f( x-v.x ,  y-v.y ,  z-v.z); }
	Vector3f operator += (const Vector3f& v)const { return Vector3f( x+v.x ,  y+v.y ,  z+v.z); }
	Vector3f operator -()const { return Vector3f( -x ,  -y ,  -z); }

	float norm() const{ return std::sqrt(x * x + y * y + z * z); }
	Vector3f normalized() const { float n = norm(); return Vector3f(x / n, y / n, z / n); }


	float operator [](int index)  { return (&x)[index]; }
	
	friend Vector3f operator *(float &r, Vector3f& v)
	{
		return Vector3f(r*v.x,r*v.y,r*v.z);
	}

	static Vector3f Max(const Vector3f& v1, const Vector3f& v2)
	{
		return Vector3f(std::fmax(v1.x, v2.x),
			std::fmax(v1.y, v2.y),
			std::fmax(v1.z, v2.z));
	}

	static Vector3f Min(const Vector3f& v1, const Vector3f& v2)
	{
		return Vector3f(std::fmin(v1.x, v2.x),
			std::fmin(v1.y, v2.y),
			std::fmin(v1.z, v2.z));
	}

	float x, y, z;
};

inline float DotProduct(const Vector3f& v1, const Vector3f& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
inline Vector3f CrossProduct(const Vector3f& v1, const Vector3f& v2)
{
	return Vector3f(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}
#endif // !VECTOR_HPP
