#pragma once

#include "Transform.h"


class Light: public ITransformable
{
public:
	glm::vec3 color{1};
	float intensity{1};
};


class SpotLight: public Light
{
public:
	
};