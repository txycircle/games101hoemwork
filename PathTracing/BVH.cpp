#include <algorithm>
#include "BVH.hpp"
#include <iostream>
#include <vector>
#include "vector.hpp"
//#include "Bounds3.hpp"
#include "Intersection.hpp"
#include "object.hpp"
#include "common.hpp"





BVHBuildNode* BVHAccel::RecursiveBuild(std::vector<Object*> p)
{
	BVHBuildNode* node = new BVHBuildNode();
	if (p.size() == 1)
	{
		Object* obj = p[0];
		node->object = obj;
		node->area = obj->GetArea();
		node->bounds = obj->GetBounds();
		node->left = nullptr;
		node->right = nullptr;
	}
	else
	{
		if (p.size() == 2)
		{
			node->left = RecursiveBuild(std::vector<Object*> {p[0]});
			node->right = RecursiveBuild(std::vector<Object*> {p[1]});
			node->area = node->left->area + node->right->area;
			node->bounds = Union(node->left->bounds, node->right->bounds);
		}
		else
		{
			Bounds3 centriod;
			for (int i=0;i<p.size();++i)
			{
				centriod = Union(centriod, p[i]->GetBounds().Centriod());
			}
			int dim = centriod.MaxExtent();
			switch (dim)
			{
				case 0:
					std::sort(p.begin(), p.end(), [](Object* o1, Object* o2) {return o1->GetBounds().Centriod().x < o2->GetBounds().Centriod().x; });
					break;
				case 1:
					std::sort(p.begin(), p.end(), [](Object* o1, Object* o2) {return o1->GetBounds().Centriod().y < o2->GetBounds().Centriod().y; });
					break;
				case 2:
					std::sort(p.begin(), p.end(), [](Object* o1, Object* o2) {return o1->GetBounds().Centriod().z < o2->GetBounds().Centriod().z; });
					break;
				default:
					break;
			}
			auto begining = p.begin();
			auto ending = p.end();
			auto middle = begining + (p.size() / 2);

			
			std::vector<Object*> pLeft = std::vector<Object*> (begining,middle);
			std::vector<Object*> pRight = std::vector<Object*> (middle,ending);

			node->left = RecursiveBuild(pLeft);
			node->right = RecursiveBuild(pRight);

			node->bounds = Union(node->left->bounds, node->right->bounds);

			node->area = node->left->area + node->right->area;
		}
	}
	return node;
}


Intersection BVHAccel::GetIntersection(const Ray& _ray, BVHBuildNode* node)
{
	Intersection return_intersection;
	Bounds3 bound = node->bounds;
	if (bound.IntersectionP(_ray) == true)
	{
		if (node->left == nullptr && node->right == nullptr)
		{
			return_intersection =  node->object->GetIntersection(_ray);
		}
		else
		{
			Intersection left = BVHAccel::GetIntersection(_ray, node->left);
			Intersection right = BVHAccel::GetIntersection(_ray, node->right);
			if(left.happend==true && right.happend==true)
				return_intersection =  left.dis < right.dis ? left : right;
			else
				if (left.happend == false) return_intersection =  right;
				else return_intersection = left;
		}
	}
	return return_intersection;
}

Intersection BVHAccel::Intersect(const Ray& _ray)
{
	Intersection pos;
	if (!root)
		return pos;
	return BVHAccel::GetIntersection(_ray, root);
}


void BVHAccel::GetSample(Intersection& pos, float& pdf, float p,BVHBuildNode* node)
{
	if (node->left==nullptr||node->right==nullptr)
	{
		node->object->Sample(pos, pdf);
		pdf *= node->area;
	}
	else
	{
		if (p < node->left->area)
			GetSample(pos, pdf, p, node->left);
		else
			GetSample(pos, pdf, p - node->left->area, node->right);
	}
}


void BVHAccel::Sample(Intersection& pos, float& pdf)
{
	float p = std::sqrt(GetRandomFloat()) * root->area;
	GetSample(pos, pdf, p,root);
	pdf = 1 / root->area;
}

BVHBuildNode::BVHBuildNode() :bounds(Bounds3()), left(nullptr), right(nullptr), object(nullptr), area(0.0f) {}
