#pragma once

#include "Transform.h"


class Light: public ITransformable
{
public:
	Light(float intensity = 1.f, glm::vec3 color = {1.f, 1.f, 1.f});
	
	float intensity;
	glm::vec3 color;
};
