#pragma once

#include "SDL.h"
#include "fish.h"
#include <vector>
#include <list>

class Aquarium {
public:
	Aquarium(const SDL_Rect&);
	void update();
	void add_fish(const size_t);
	void free_sdl_data();
private:
	std::vector<SDL_Texture*> fish_textures;
	std::list<Fish> shoal;

	SDL_Texture* background_texture;
	SDL_Rect aquarium_rectangle;
};