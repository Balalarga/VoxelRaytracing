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

		if (HitResult hit = Intersect(std::move(ray)))
		{
			pixel.color = hit.object->GetMaterial().color;
			
			Ray lightRay;
			lightRay.direction = ray.Reflect(hit.normal);
			// offset the original point to avoid occlusion by the object itself
			float scalar = lightRay.direction.x*hit.normal.x+lightRay.direction.y*hit.normal.y+lightRay.direction.z * hit.normal.z;
			lightRay.origin = scalar < 0 ? hit.point - hit.normal * 1e-3f : hit.point + hit.normal * 1e-3f;
		}
		else
		{
			pixel.color = _backgroundColor;	
		}
	});
}

HitResult Scene::Intersect(Ray&& ray)
{
	HitResult closestHit;
	closestHit.distance = std::numeric_limits<float>::max();
	for (IHittable*& obj : _objects)
	{
		HitResult hit = obj->Hit(ray);
		if (closestHit.distance > hit.distance)
			closestHit = hit;
	}
	
	return closestHit;
}
