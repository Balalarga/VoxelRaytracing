#include "Scene.h"

#include "Graphics/Texture.h"
#include "GlmUtils.h"
#include "Light.h"


void Scene::RenderOn(Texture& texture)
{
	float aspectRatio = (float)texture.Size().x / (float)texture.Size().y;
	texture.Edit([this, aspectRatio](PixelData pixel)
	{
		Ray ray;
		ray.origin = {0.f, 0.f, 0.f};
		float rx = (pixel.ux * 2.f - 1.f) * aspectRatio;
		float ry = pixel.uy * 2.f - 1.f;
		ray.direction = {rx, ry, -1.f};
		
		glm::vec3 sceneColor = Render(pixel, ray, _bounsDepth);
		
		pixel.color = {
			static_cast<Uint8>(sceneColor.r * 255.f),
			static_cast<Uint8>(sceneColor.g * 255.f),
			static_cast<Uint8>(sceneColor.b * 255.f),
			255};
	});
}

glm::vec3 Scene::Render(PixelData& pixel, const Ray& ray, int bounsDepth)
{
	if (bounsDepth == 0)
		return _backgroundColor;
	
	if (HitResult hit = Intersect(ray))
	{
		const Material& material = hit.object->GetMaterial();

		glm::vec3 diffuse{0};
		glm::vec3 specular{0};
		for (Light* light: _lights)
		{
			glm::vec3 lightDir = normalize(light->GetPosition() - hit.point);
			float diff = std::max(dot(hit.normal, lightDir), 0.f);
			diffuse += diff * light->color * light->intensity;

			glm::vec3 reflectDir = reflect(lightDir, hit.normal);
			float spec = pow(std::max(dot(ray.direction, reflectDir), 0.0f), material.shiningExponent);
			specular += material.specularStrength * spec * light->color * light->intensity;
		}
		diffuse *=  material.diffuseColor;
		specular *= material.specularColor;
		return diffuse + specular;
	}
	
	return _backgroundColor;
}

HitResult Scene::Intersect(const Ray& ray)
{
	HitResult closestHit;
	for (IHittable*& obj : _objects)
	{
		HitResult hit = obj->Hit(ray);
		if (hit.distance < closestHit.distance)
			closestHit = hit;
	}
	
	return closestHit;
}
