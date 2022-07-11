#pragma once
#include <glm/vec3.hpp>

#include "Material.h"
#include "Ray.h"


class IHittable;

struct HitResult
{
	glm::vec3 point{0};
	glm::vec3 normal{0};
	IHittable* object{};
	
	operator bool() const { return object != nullptr; }
};

class IHittable
{
public:
	IHittable(const Material& material): material(material) {}
	virtual ~IHittable() = default;

	virtual HitResult Hit(Ray ray) = 0;

	Material material;
	glm::vec3 position{0};
};

class Sphere: public IHittable
{
public:
	Sphere(const Material& material);

	HitResult Hit(Ray ray) override;
	
	float radius = 1.f;
};