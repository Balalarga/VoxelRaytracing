#pragma once
#include <glm/vec3.hpp>

#include "Material.h"
#include "Ray.h"
#include "Transform.h"


class IHittable;

struct HitResult
{
	IHittable* object{};
	glm::vec3 point{0};
	glm::vec3 normal{0};
	
	operator bool() const { return object != nullptr; }
};

class IHittable: public ITransformable
{
public:
	IHittable(const Material& inMaterial = sDefaultMaterial);
	virtual ~IHittable() = default;

	virtual HitResult Hit(Ray ray) = 0;

	virtual void SetMaterial(const Material& newMaterial);
	const Material& GetMaterial() const { return _material; }

	
protected:
	Material _material;
	
	static Material sDefaultMaterial;
};


class Sphere: public IHittable
{
public:
	Sphere(float radius = 1.f, const Material& inMaterial = sDefaultMaterial);

	HitResult Hit(Ray ray) override;
	
	float radius;
};

class Cube: public IHittable
{
public:
	Cube(float size = 1.f, const Material& inMaterial = sDefaultMaterial);
	
	void SetPosition(const glm::vec3& newPosition) override;
	
	// Optimized slab method
	HitResult Hit(Ray ray) override;
	
	float size;
	
private:
	glm::vec3 _bounds[2]{};
};