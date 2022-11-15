#pragma once

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "common.hpp"
#include "vector.hpp"

enum class MaterialType { DIFFUSE };
class Material
{

private:
	Vector3f toWorld(const Vector3f& a, const Vector3f& N) {//todo
		Vector3f B, C;
		if (std::fabs(N.x) > std::fabs(N.y)) {
			float invLen = 1.0f / std::sqrt(N.x * N.x + N.z * N.z);
			C = Vector3f(N.z * invLen, 0.0f, -N.x * invLen);
		}
		else {
			float invLen = 1.0f / std::sqrt(N.y * N.y + N.z * N.z);
			C = Vector3f(0.0f, N.z * invLen, -N.y * invLen);
		}
		B = CrossProduct(C, N);
		return  B*a.x + C*a.y  + N*a.z;
	}
public:
	
	MaterialType M_Type;
	Vector3f M_Emission;
	Vector3f kd, ks;
	float Specular_Exponent;
	//Material() {};
	Material(MaterialType type = MaterialType:: DIFFUSE, Vector3f e = Vector3f(0,0,0));
	Vector3f GetEmission() { return M_Emission; }
	bool HasEmission() { if (GetEmission().norm() > 0.0) return true; return false; }
	Vector3f Sample(const Vector3f& wi, const Vector3f& normal);
	float pdf(const Vector3f& wi,const Vector3f&wo, const Vector3f& normal);
	Vector3f Eval(const Vector3f& wi,const Vector3f&wo, const Vector3f& normal);
};

#endif // !MATERIAL_HPP
