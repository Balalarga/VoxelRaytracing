#pragma once


#include <glm/glm.hpp>


struct Ray
{
	glm::vec3 origin{0};
	glm::vec3 direction{0};
	
	glm::vec3 at(float t)
	{
		return origin + direction * t;
	}
};
