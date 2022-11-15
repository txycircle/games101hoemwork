#include"material.hpp"



Material::Material(MaterialType type, Vector3f e) :Specular_Exponent(0.0f)
{
	M_Type = type;
	M_Emission = e;
}
Vector3f Material::Eval(const Vector3f& wi, const Vector3f& wo, const Vector3f& normal)
{
	switch (M_Type)
	{
	case MaterialType::DIFFUSE:
		float cosalpha = DotProduct(wo, normal);
		if (cosalpha > 0.0f)
		{
			return kd / MY_PI;
		}
		else
			return Vector3f(0.0f, 0.0f, 0.0f);
		break;
	}
}

Vector3f Material::Sample(const Vector3f& wi, const Vector3f& normal)
{
	switch (M_Type)
	{
	case MaterialType::DIFFUSE:
		float z = GetRandomFloat();
		float a = std::sqrt(1 - z * z);
		float b = GetRandomFloat();
		float x = std::cos(2 * MY_PI * b) * a;
		float y = std::sin(2 * MY_PI * b) * a;
		Vector3f localray(x, y, z);
		return toWorld(localray, normal);



	}
}

float Material::pdf(const Vector3f& wi, const Vector3f& wo, const Vector3f& normal)
{
	switch (M_Type)
	{
	case MaterialType::DIFFUSE:
		float cosalpha = DotProduct(wo, normal);
		if (cosalpha > 0.0f)
			return 1.0f / (2 * MY_PI);
		else
			return 0.0f;

	}
}
