
#include "vector.hpp"
#include "BVH.hpp"
#include "Intersection.hpp"
#include "common.hpp"
#include "Ray.hpp"
#include "object.hpp"
#include "material.hpp"
#include "Scene.hpp"

void Scene::BuildBvh()
{
	this->bvh = new BVHAccel(objects);
}


void Scene::SampleLight(Intersection & pos, float& pdf)
{
	//面光源采用object采样
	int surfacearea = 0;
	for (auto obj : objects)
	{
		if (obj->HasEmit() == true)
		{
			surfacearea += obj->GetArea();
		}
	} 
	float p = GetRandomFloat();
	int areas = 0;
	float threld = p * surfacearea;
	for (auto obj : objects)
	{
		if (obj->HasEmit() == true)
		{
			if (areas >= threld)
			{
				obj->Sample(pos, pdf);
				break;
			}
			else
				areas += obj->GetArea();
		}
	}
}

Intersection Scene::intersect(const Ray& ray)
{
	return this->bvh->Intersect(ray);
}
Vector3f Scene::CastRay(const Ray& ray, int depth)
{
	Vector3f returnColor(0.0, 0.0, 0.0);
	Intersection inter = intersect(ray);
	if (inter.happend == false)
	{
		return returnColor;
	}
	//与光源相交
	if (inter.m->HasEmission()==true)
	{
		return inter.m->GetEmission();
	}

	Vector3f wo = ray.dir.normalized();

	//与物体相交
	Intersection interLight;
	float pdfLight = 0;
	SampleLight(interLight, pdfLight);

	Vector3f wi = (interLight.coord - inter.coord).normalized();
	float disLight = (interLight.coord - inter.coord).norm();
	Ray rayLight(inter.coord, wi);

	Intersection interCheck = intersect(rayLight);
	if (interCheck.dis >= disLight)
	{
		Vector3f eval = inter.m->Eval(wi,wo,inter.normal.normalized());
		float cosine = DotProduct(inter.normal.normalized(), wi);
		float cosineLight = DotProduct(interLight.normal.normalized(), -wi);
		returnColor += interLight.emit * eval * cosine * cosineLight / std::pow(disLight, 2) / pdfLight;
	}

	float p = GetRandomFloat();
	if (p < RussianRoulette)
	{
		Vector3f wi = inter.m->Sample(wo, inter.normal.normalized());
		Ray rayObj(inter.coord, wi);
		Intersection interObj = intersect(rayObj);
		if (interObj.happend)
		{
			Vector3f eval = inter.m->Eval(wi, wo, inter.normal.normalized());
			float cosine = DotProduct(inter.normal.normalized(), wi);
			float pdf = inter.m->pdf(wi,wo,inter.normal.normalized());
			returnColor += CastRay(rayObj,depth+1) * eval * cosine / pdf / RussianRoulette;
		}
	}
	
	return returnColor;
}