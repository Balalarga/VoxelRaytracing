#pragma once


#include <glm/glm.hpp>


struct Ray
{
	glm::vec3 origin{0};
	glm::vec3 direction{0};
	
	glm::vec3 At(float t)
	{
		return origin + direction * t;
	}
	
	glm::vec3 Reflect(const glm::vec3& normal)
	{
		return normalize(direction - normal * 2.f * (direction * normal));
	}
};
