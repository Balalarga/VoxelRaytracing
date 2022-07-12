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
		return -2;
	}

	Scene scene;
	
	Sphere sphere(1.f);
	sphere.SetPosition({0, 0, 5});
	scene.AddHittable(&sphere);
	
	Cube cube(1.f);
	cube.SetPosition({2, 0, 5});
	scene.AddHittable(&cube);
	
	bool quit = false;
	while (!quit)
	{
		quit = PollEvents();
		
		SDL_Rect textureRect{0, 0, texture.Size().x, texture.Size().y};
		window->Bind(texture);
		window->Clear();
		scene.RenderOn(texture);
		
		window->Bind();
		window->Clear();
		window->Render(texture, textureRect);
		window->Update();
	}

	RendererWindow::Destroy();
	return 0;
}
