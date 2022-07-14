#include <iostream>
#include <SDL.h>
#include <thread>

#include "Graphics/RendererWindow.h"
#include "Graphics/Texture.h"
#include "Tracing/Scene.h"


bool PollEvents()
{
	bool quit = false;
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT || (e.type==SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE))
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
	
	Light light;
	light.SetPosition({2, 0, 0});
	scene.AddLight(&light);
	
	Sphere sphere(1.f);
	sphere.SetPosition({0, 0, 5});
	scene.AddHittable(&sphere);
	
	Sphere sphere2(2.f);
	sphere2.SetPosition({2, 0, 5});
	scene.AddHittable(&sphere2);
	
	Plane plane(glm::vec3(0.f, 1.f, 0.f));
	plane.SetPosition({0, -3, 0});
	scene.AddHittable(&plane);
	
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
