#pragma once
#include <SDL_pixels.h>


struct Material
{
	Material(SDL_Color color): color(color) {}
	SDL_Color color{255, 255 , 255, 0};
};
