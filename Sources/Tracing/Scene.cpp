#include "Scene.h"

#include "Graphics/Texture.h"
#include "GlmUtils.h"
#include "Light.h"

glm::vec3 sGlobalAmbient{1, 1, 1};

SDL_Color toSdlColor(const glm::vec3& fColor)
{
	return {
		static_cast<Uint8>(fColor.r * 255.f),
		static_cast<Uint8>(fColor.g * 255.f),
		static_cast<Uint8>(fColor.b * 255.f),
		255
	};
}


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

		if (HitResult hit = Intersect(ray))
		{
			Material material = hit.object->GetMaterial();
			if (_lights.empty())
			{
				pixel.color = toSdlColor(material.diffuse);
				return;
			}
			material.ambient *= sGlobalAmbient;

			glm::vec3 lightDir = normalize(_lights[0]->GetPosition() - hit.point);
			float diffuseLight = std::max(dot(hit.normal, lightDir), 0.f);
			material.diffuse *= _lights[0]->color * diffuseLight;
			
			glm::vec3 rayInvDir = normalize(ray.origin - hit.point);
			glm::vec3 H = normalize(lightDir + rayInvDir);
			float specularLight = pow(std::max(dot(hit.normal, H), 0.f), material.shininess);
			if (diffuseLight <= 0)
				specularLight = 0;
			material.specular *= _lights[0]->color * specularLight;

			// pixel.color = toSdlColor(material.diffuse);
			pixel.color = toSdlColor(material.ambient + material.diffuse + material.specular + material.emissive);
		}
		else
		{
			pixel.color = _backgroundColor;
		}
	});
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
