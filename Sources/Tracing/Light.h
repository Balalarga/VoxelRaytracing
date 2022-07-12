#pragma once

#include <SDL_pixels.h>

#include "Transform.h"


class Light: public ITransformable
{
public:
	Light(float intensity = 1.f, SDL_Color color = {255, 255, 255, 255});
	
	float intensity;
	SDL_Color color;
};
