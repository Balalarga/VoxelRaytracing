#include "Scene.h"

#include "Graphics/Texture.h"


void Scene::RenderOn(Texture& texture)
{
	texture.Edit([this](PixelData pixelData)
	{
		Ray ray;
		ray.origin = {0.f, 0.f, 0.f};
		float nx = (pixelData.ux * 2.f - 1.f) * pixelData.aspectRatio;
		float ny = pixelData.uy * 2.f - 1.f;
		ray.direction = {nx, ny, -1.f};
		FillTexture(pixelData, ray);
	});
}

void Scene::FillTexture(PixelData pixelData, Ray ray)
{
	for (IHittable*& obj : _objects)
	{
		HitResult hit = obj->Hit(ray);
		if (hit)
		{
			pixelData.color = hit.object->material.color;
			return;
		}
	}
}
