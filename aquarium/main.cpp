#include "menu.h"
#include "SDL.h"
#include <time.h>

// event handler
SDL_Event e;

SDL_Window* main_window;

SDL_Renderer* main_renderer;

inline bool is_quit(const SDL_Event& e)
{
	return e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE);
}

inline void run_update_loop(Aquarium& aquarium, Menu& menu)
{
	while (true) {
		aquarium.update();

		// handle user input
		while (SDL_PollEvent(&e)) {
			if (is_quit(e))
				return;
			menu.handle_input(e);
		}

		// update window
		SDL_RenderPresent(main_renderer);
	}
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		MessageBoxA(NULL, SDL_GetError(), NULL, MB_OK);
		exit(-1);
	}

	// initialize images loading
	check_for_null(IMG_Init(IMG_INIT_PNG), IMG_GetError);

	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	// create fullscreen window
	main_window = check_for_null(
		SDL_CreateWindow("Aquarium", 0, 0,
			dm.w, dm.h, SDL_WINDOW_FULLSCREEN_DESKTOP), SDL_GetError);

	main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);

	// draw menu background
	SDL_SetRenderDrawColor(main_renderer, 192, 192, 192, 0);
	// clear menu window
	SDL_RenderClear(main_renderer);

	// initialise aquarium and menu
	Aquarium aquarium({ 0, 100, dm.w, dm.h - 100 });
	Menu menu({ 0, 0, dm.w, dm.h }, aquarium);

	run_update_loop(aquarium, menu);

	aquarium.free_sdl_data();
	menu.free_sdl_data();
	SDL_DestroyWindow(main_window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}