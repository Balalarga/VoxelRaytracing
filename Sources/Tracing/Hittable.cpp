#include "Hittable.h"

Material IHittable::sDefaultMaterial({150, 50, 50, 0});

IHittable::IHittable(const Material& inMaterial):
	_material(inMaterial)
{
}

void IHittable::SetMaterial(const Material& newMaterial)
{
	_material = newMaterial;
}

Sphere::Sphere(float radius, const Material& inMaterial):
	IHittable(inMaterial),
	radius(radius)
{
}

HitResult Sphere::Hit(Ray ray)
{
	HitResult result;

	glm::vec3 oc = ray.origin - GetPosition();
	float a = dot(ray.direction, ray.direction);
	float b = 2.f * dot(oc, ray.direction);
	float c = dot(oc,oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	
	if (discriminant >= 0)
	{
		result.object = this;
	}
	
	return result;
}

Cube::Cube(float size, const Material& inMaterial):
	IHittable(inMaterial),
	size(size)
{
	_bounds[0] = GetPosition() - glm::vec3(size) / 2.0f;
	_bounds[1] = GetPosition() + glm::vec3(size) / 2.0f;
}

void Cube::SetPosition(const glm::vec3& newPosition)
{
	IHittable::SetPosition(newPosition);
	_bounds[0] = newPosition - glm::vec3(size) / 2.0f;
	_bounds[1] = newPosition + glm::vec3(size) / 2.0f;
}

HitResult Cube::Hit(Ray ray)
{
	glm::vec3 invDir = 1.f / ray.direction;
	int sign[3]{
		invDir.x < 0,
		invDir.y < 0,
		invDir.z < 0};

	float tmin = (_bounds[sign[0]].x - ray.origin.x) * invDir.x;
	float tmax = (_bounds[1 - sign[0]].x - ray.origin.x) * invDir.x;
	float tymin = (_bounds[sign[1]].y - ray.origin.y) * invDir.y;
	float tymax = (_bounds[1 - sign[1]].y - ray.origin.y) * invDir.y;

	if ((tmin > tymax) || (tymin > tmax))
		return {};

	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (_bounds[sign[2]].z - ray.origin.z) * invDir.z;
	float tzmax = (_bounds[1 - sign[2]].z - ray.origin.z) * invDir.z;

	if ((tmin > tzmax) || (tzmin > tmax))
		return {};

	// if (tzmin > tmin)
	// 	tmin = tzmin;
	// if (tzmax < tmax)
	// 	tmax = tzmax;
	// hit.distance = tmin;
	// hit.normal = Vec3f(mimage.c[0], mimage.c[1], -mimage.c[3]);
	// hit.pos = ray.Origin + ray.Dir * hit.distance;
	
	return {this};
}
