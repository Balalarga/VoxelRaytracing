#pragma once
#include <vector>

#include "Hittable.h"
#include "Light.h"
#include "Graphics/Texture.h"


class Scene
{
public:
	Scene() = default;

	void RenderOn(Texture& texture);
	
	void AddHittable(IHittable* hittable) { _objects.push_back(hittable); }
	void AddLight(Light* light) { _lights.push_back(light); }

protected:
	glm::vec3 Render(PixelData& pixel, const Ray& ray, int bounsDepth);
	HitResult Intersect(const Ray& ray);
	
private:
	int _bounsDepth = 5;
	std::vector<IHittable*> _objects;
    std::vector<Light*> _lights;
	glm::vec3 _backgroundColor{0.2, 0.2, 0.2};
};
