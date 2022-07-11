#pragma once
#include <vector>

#include "Hittable.h"
#include "Graphics/Texture.h"


class Scene
{
public:
	Scene() = default;

	void RenderOn(Texture& texture);
	void FillTexture(PixelData pixelData, Ray ray);
	
	void AddHittable(IHittable* hittable)
	{
		_objects.push_back(hittable);
	}
	
private:
	std::vector<IHittable*> _objects;
	
};
