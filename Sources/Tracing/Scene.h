#pragma once
#include <vector>

#include "Hittable.h"
#include "Graphics/Texture.h"


class Light;

class Scene
{
public:
	Scene() = default;

	void RenderOn(Texture& texture);
	
	void AddHittable(IHittable* hittable) { _objects.push_back(hittable); }
	void AddLight(Light* light) { _lights.push_back(light); }

	
private:
	std::vector<IHittable*> _objects;
    std::vector<Light*> _lights;
	SDL_Color _backgroundColor{40, 40, 40, 0};
};
