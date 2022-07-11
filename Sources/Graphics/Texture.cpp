#include "Texture.h"

#include <iostream>


Texture::Texture(SDL_Renderer* renderer, SDL_Point size):
	_size(size)
{
	_sdlTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		size.x,
		size.y);
	
	if (!_sdlTexture)
		return;
	
	_wasInited = true;
}

SDL_Color& GetPixel(SDL_Color* pixels, int x, int y, int w)
{
	return pixels[y * w + x];
}

Texture::~Texture()
{
	if (_sdlTexture)
		SDL_DestroyTexture(_sdlTexture);
}

void Texture::Edit(void(*func)(SDL_Color&, float, float))
{
	SDL_Rect lockRect{0, 0, _size.x, _size.y};
	SDL_Color* pixels{};
	int pitch;
	if (SDL_LockTexture(_sdlTexture, &lockRect, (void**)&pixels, &pitch) != 0)
	{
		std::cout<<SDL_GetError()<<std::endl;
		return;
	}
	
	for (int x = 0; x < _size.x; ++x)
	{
		float ux = static_cast<float>(x) / static_cast<float>(_size.x);
		for (int y = 0; y < _size.y; ++y)
		{
			float uy = static_cast<float>(y) / static_cast<float>(_size.y);
			func(GetPixel(pixels, x, y, _size.x), ux, uy);
		}
	}
	SDL_UnlockTexture(_sdlTexture);
}
