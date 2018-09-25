#pragma once

#include "SDL.h"
#include "aquarium.h"
#include <vector>

class Menu {
public:
	Menu(const SDL_Rect&, Aquarium&);
	void handle_input(const SDL_Event&);
	void free_sdl_data();
private:
	struct Button {
		Button(SDL_Texture*, const int, const int);
		SDL_Texture* texture;
		SDL_Rect rectangle;
		bool selected = false;
	};

	Aquarium& aquarium;
	SDL_Rect menu_rectangle;
	std::vector<Button> menu_buttons;
};