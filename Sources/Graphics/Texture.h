#pragma once

#include <functional>
#include <SDL.h>

class PixelData
{
public:
	PixelData(SDL_Color& color, float ux, float uy, float aspect_ratio)
		: color(color),
		ux(ux),
		uy(uy),
		aspectRatio(aspect_ratio) {}

	SDL_Color& color;
	float ux, uy;
	float aspectRatio;
};


class Texture
{
	friend class RendererWindow;
	SDL_Texture* SdlTexture() { return _sdlTexture; }
public:
	Texture(SDL_Renderer* renderer, SDL_Point size);
	~Texture();

	bool WasInited() const { return _wasInited; }
	const SDL_Point& Size() const { return _size; }
	
	void Edit(std::function<void(PixelData)> func);
	
	
private:
	bool _wasInited = false;
	SDL_Point _size;
	SDL_Texture* _sdlTexture{};
};
