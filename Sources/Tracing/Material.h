#pragma once
#include <SDL_pixels.h>


struct Material
{
	glm::vec3 emissive{};
	glm::vec3 ambient{};
	glm::vec3 diffuse{};
	glm::vec3 specular{};
	float shininess = 1.f;
};
