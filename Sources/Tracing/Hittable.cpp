#include "Hittable.h"

Material IHittable::sDefaultMaterial(
	{0.0, 0.0, 0.0},
	{0.6, 0.2, 0.2},
	{0.3, 0.1, 0.1},
	{0, 0, 0}
	);

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

HitResult Sphere::Hit(const Ray& ray)
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
		result.distance = (-b - sqrt(discriminant)) / (2 * a);
		result.point = ray.At(result.distance);
		result.normal = GetPosition() - result.point;
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

HitResult Cube::Hit(const Ray& ray)
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

	if (tmin > tzmax || tzmin > tmax)
		return {};
	
	HitResult result;
	result.object = this;
	
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	
	result.distance = tmin;
	result.point = ray.At(result.distance);
	glm::vec3 sphereNormal = GetPosition() - result.point;
	auto fsign = [](float value) -> float
	{
		return value > 0 ? 1 : -1;
	};
	if (abs(sphereNormal.x) > abs(sphereNormal.y) && abs(sphereNormal.x) > abs(sphereNormal.z))
		result.normal = {fsign(sphereNormal.x), 0.f, 0.f};
	else if (abs(sphereNormal.y) > abs(sphereNormal.x) && abs(sphereNormal.y) > abs(sphereNormal.z))
		result.normal = {0.f, fsign(sphereNormal.y), 0.f};
	else
		result.normal = {0.f, 0.f, fsign(sphereNormal.z)};
	
	return result;
}

Plane::Plane(const glm::vec3& normal, const Material& inMaterial):
	IHittable(inMaterial),
	normal(-normal)
{
}

HitResult Plane::Hit(const Ray& ray)
{
	constexpr float eps = 0.0001f;
	HitResult hit;
	float denom = dot(normal, ray.direction);
	if (abs(denom) > eps)
	{
		float t = dot(ray.origin - GetPosition(), normal) / denom;
		if (t >= eps)
		{
			hit.normal = normal;
			hit.distance = t;
			hit.object = this;
			hit.point = ray.At(hit.distance);
		}
	}
	return hit;
}
