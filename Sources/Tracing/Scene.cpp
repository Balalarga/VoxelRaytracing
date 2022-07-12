#include "Scene.h"

#include "Graphics/Texture.h"


void Scene::RenderOn(Texture& texture)
{
	float aspectRatio = (float)texture.Size().x / (float)texture.Size().y;
	texture.Edit([this, aspectRatio](PixelData pixel)
	{
		Ray ray;
		ray.origin = {0.f, 0.f, 0.f};
		float nx = (pixel.ux * 2.f - 1.f) * aspectRatio;
		float ny = pixel.uy * 2.f - 1.f;
		ray.direction = {nx, ny, -1.f};

		for (IHittable*& obj : _objects)
		{
			HitResult hit = obj->Hit(ray);
			if (hit)
			{
				pixel.color = hit.object->GetMaterial().color;
				return;
			}
		}
		pixel.color = _backgroundColor;
	});
}
