#include "Hittable.h"


Sphere::Sphere(const Material& material):
	IHittable(material)
{
}

HitResult Sphere::Hit(Ray ray)
{
	HitResult result;

	glm::vec3 oc = ray.origin - position;
	float a = dot(ray.direction, ray.direction);
	float b = 2.f * dot(oc, ray.direction);
	float c = dot(oc,oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	result.hit = discriminant > 0;
	
	if (result)
		result.object = this;
	
	return result;
}
