#include "RendererWindow.h"
#include "Texture.h"

#include <SDL_image.h>


RendererWindow* RendererWindow::_self{};


RendererWindow::RendererWindow(const std::string& title, SDL_Point windowSize):
	_windowSize(windowSize)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return;
	}

	_sdlWindow = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowSize.x,
		windowSize.y,
		SDL_WINDOW_SHOWN);
	
	if (_sdlWindow == nullptr)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}
	
	_sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (_sdlRenderer == nullptr)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return;
	}

	_screenTexture = new Texture(_sdlRenderer, {});
	if (!_screenTexture)
		return;
	
	_wasInited = true;
}

RendererWindow* RendererWindow::Self()
{
	return _self;
}

RendererWindow* RendererWindow::Init(const std::string& title, SDL_Point windowSize)
{
	if (!_self)
		_self = new RendererWindow(title, windowSize);
	
	return _self;
}

void RendererWindow::Destroy()
{
	delete _self;
}

RendererWindow::~RendererWindow()
{
	if (_sdlRenderer)
		SDL_DestroyRenderer(_sdlRenderer);
	if (_sdlWindow)
		SDL_DestroyWindow(_sdlWindow);
	if (_screenTexture)
		delete _screenTexture;
	
	IMG_Quit();
	SDL_Quit();
}

void RendererWindow::Clear()
{
	SDL_RenderClear(_sdlRenderer);
}

void RendererWindow::Clear(SDL_Color color)
{
	SDL_SetRenderDrawColor(_sdlRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(_sdlRenderer);
}

void RendererWindow::Bind()
{
	SDL_SetRenderTarget(_sdlRenderer, nullptr);
}

void RendererWindow::Bind(Texture& texture)
{
	SDL_SetRenderTarget(_sdlRenderer, texture.SdlTexture());
}

void RendererWindow::Render(Texture& texture, SDL_Rect textureRect)
{
	SDL_RenderCopy(_sdlRenderer, texture.SdlTexture(), nullptr, &textureRect);
}

void RendererWindow::Update()
{
	SDL_RenderPresent(_sdlRenderer);
}
