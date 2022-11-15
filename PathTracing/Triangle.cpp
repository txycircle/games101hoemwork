#include "Triangle.hpp"
#include "common.hpp"
#include "BVH.hpp"
#include "Intersection.hpp"
#include "OBJ_Loader.hpp"


Triangle::Triangle(Vector3f _v1, Vector3f _v2, Vector3f _v3, Material* _m) :v1(_v1), v2(_v2), v3(_v3), m(_m)
{
	e1 = v2 - v1;
	e2 = v3 - v1;
	area = 0.5f * CrossProduct(e1, e2).norm();
	normal = CrossProduct(e1, e2).normalized();
	std::vector<Vector3f> vs{ v1,v2,v3 };
	BoundingBox = Bounds3(vs);
}

void Triangle::Sample(Intersection& pos, float& pdf)
{
	float r1 = std::sqrt(GetRandomFloat());
	float r2 = GetRandomFloat();
    pos.coord = v1 * (1.0f - r1) + v2 * r1 * (1.0f - r2) + v3 * r1 * r2;
	pos.normal = normal;
	pdf = 1 / area;
}

Bounds3 Triangle::GetBounds()
{
	return BoundingBox;
}


Intersection Triangle::GetIntersection(const Ray& ray)
{
    Intersection inter;

    if (DotProduct(ray.dir, normal) > 0)
        return inter;
    double u, v, t_tmp = 0;
    Vector3f pvec = CrossProduct(ray.dir, e2);
    double det = DotProduct(e1, pvec);
    if (fabs(det) < EPSILON)
        return inter;

    double det_inv = 1. / det;
    Vector3f tvec = ray.origin - v1;
    u = DotProduct(tvec, pvec) * det_inv;
    if (u < 0 || u > 1)
        return inter;
    Vector3f qvec = CrossProduct(tvec, e1);
    v = DotProduct(ray.dir, qvec) * det_inv;
    if (v < 0 || u + v > 1)
        return inter;
    t_tmp = DotProduct(e2, qvec) * det_inv;

    // TODO find ray triangle intersection
    if (t_tmp > 0)
    {
        inter.happend = true;
        inter.dis = t_tmp;
        inter.obj = this;
        inter.normal = normal;
        inter.coord = ray(t_tmp);
        inter.m = m;
    }

    return inter;
}

TriangleMesh::TriangleMesh(const std::string& filename, Material* _m)
{
	objl::Loader loader;
	loader.LoadFile(filename);
	area = 0;
	m = _m;

	auto mesh = loader.LoadedMeshes[0];
	Vector3f pMin(std::numeric_limits<float>::infinity(),
		std::numeric_limits<float>::infinity(),
		std::numeric_limits<float>::infinity());
	Vector3f pMax(-std::numeric_limits<float>::infinity(),
		-std::numeric_limits<float>::infinity(),
		-std::numeric_limits<float>::infinity());

	TriangleNums = mesh.Vertices.size() / 3;


	for (int i = 0; i < mesh.Vertices.size(); i += 3)
	{
		std::array<Vector3f, 3> faceV;
		for (int j = 0; j < 3; ++j)
		{
			Vector3f v = Vector3f(mesh.Vertices[i + j].Position.X, mesh.Vertices[i + j].Position.Y, mesh.Vertices[i + j].Position.Z);
			pMin = Vector3f::Min(pMin, v);
			pMax = Vector3f::Max(pMax, v);
			faceV[j] = v;
			//Vertices + i + j = v;
			//VertexIndex + i + j = i + j;
		}
		Triangle tri(faceV[0], faceV[1], faceV[2], m);
		Triangles.emplace_back(tri);
	}

	BoundingBox = Bounds3(pMin, pMax);

	std::vector<Object*> ptrs;
	for (auto tri : Triangles)
	{
		ptrs.push_back(&tri);
		area += tri.area;
	}
	bvh = new BVHAccel(ptrs);
}


void TriangleMesh::Sample(Intersection& pos, float& pdf)
{
	bvh->Sample(pos, pdf);
	pos.emit = m->GetEmission();
}

Bounds3 TriangleMesh::GetBounds()
{
	return BoundingBox;
}


Intersection TriangleMesh::GetIntersection(const Ray& ray)
{
	if(this->bvh)
		return this->bvh->Intersect(ray);
	return Intersection();
}
