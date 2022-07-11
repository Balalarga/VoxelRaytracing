#pragma once

#include <SDL.h>
#include <string>


class Texture;


enum class RenderTarget
{
	Renderer, Texture
};


class RendererWindow
{
public:
	static RendererWindow* Self();
	static RendererWindow* Init(const std::string& title, SDL_Point windowSize);
	static void Destroy();
	
	~RendererWindow();

	SDL_Renderer* Renderer() { return _sdlRenderer; }
	
	bool WasInited() const { return _wasInited; }
	const SDL_Point& Size() const { return _windowSize; }

	void Render(Texture& texture, SDL_Rect textureRect);
	void Clear();
	void Clear(SDL_Color color);
	void Bind();
	void Bind(Texture& texture);
	void Update();


private:
	RendererWindow(const std::string& title, SDL_Point windowSize);
	static RendererWindow* _self;
	
	bool _wasInited = false;
	SDL_Point _windowSize;
	
	SDL_Renderer* _sdlRenderer{};
	SDL_Window* _sdlWindow{};
	Texture* _screenTexture{};
};
