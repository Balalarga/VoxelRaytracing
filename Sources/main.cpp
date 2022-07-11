#include <iostream>
#include <SDL.h>
#include <thread>

#include "GlmUtils.h"
#include "Graphics/RendererWindow.h"
#include "Graphics/Texture.h"
#include "Tracing/Ray.h"
#include "Tracing/Scene.h"

bool PollEvents()
{
	bool quit = false;
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
	}
	return quit;
}


int main(int argc, char* args[])
{
	RendererWindow* window = RendererWindow::Init("VoxelRaytracing", {800, 600});
	if (!window->WasInited())
	{
		printf("Failed to initialize!\n");
		return -1;
	}
	Texture texture(window->Renderer(), {window->Size().x, window->Size().y});
	if (!texture.WasInited())
	{
		printf("Failed to initialize texture!\n");
		return -1;
	}

	Scene scene;
	Sphere sphere(Material({128, 55, 55, 0}));
	sphere.position.z += 5;
	scene.AddHittable(&sphere);
	
	bool quit = false;
	while (quit == false)
	{
		quit = PollEvents();
		
		SDL_Rect textureRect{0, 0, texture.Size().x, texture.Size().y};
		window->Bind(texture);
		window->Clear({50, 128, 50, 0});
		scene.RenderOn(texture);
		
		window->Bind();
		window->Clear({128, 50, 50, 0});
		window->Render(texture, textureRect);
		window->Update();
	}

	RendererWindow::Destroy();
	return 0;
}
