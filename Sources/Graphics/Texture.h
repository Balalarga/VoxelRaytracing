#pragma once

#include <SDL.h>


class Texture
{
	friend class RendererWindow;
	SDL_Texture* SdlTexture() { return _sdlTexture; }
public:
	Texture(SDL_Renderer* renderer, SDL_Point size);
	~Texture();

	bool WasInited() const { return _wasInited; }
	const SDL_Point& Size() const { return _size; }
	
	void Edit(void(*func)(SDL_Color&, float, float));
	
	
private:
	bool _wasInited = false;
	SDL_Point _size;
	SDL_Texture* _sdlTexture{};
};
