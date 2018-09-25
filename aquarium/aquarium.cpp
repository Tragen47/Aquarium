#include "aquarium.h"
#include "renderer.h"

Aquarium::Aquarium(const SDL_Rect& aquarium_rectangle) : aquarium_rectangle(aquarium_rectangle)
{
	// load textures for aquarium
	background_texture = load_picture("../textures/aquarium/background.png", main_renderer);

	// load fish textures
	fish_textures.emplace_back(load_picture("../textures/aquarium/pike.png", main_renderer));
	fish_textures.emplace_back(load_picture("../textures/aquarium/carp.png", main_renderer));

	// draw aquarium
	SDL_RenderCopy(main_renderer, background_texture, NULL, &aquarium_rectangle);
}

void Aquarium::update()
{
	// draw aquarium
	SDL_RenderCopy(main_renderer, background_texture, NULL, &aquarium_rectangle);

	// move and draw fishes
	for (auto& fish : shoal) {
		fish.move();
		fish.draw();
	}
}

void Aquarium::add_fish(const size_t texture_index)
{
	shoal.emplace_back(aquarium_rectangle, fish_textures[texture_index]);
}

void Aquarium::free_sdl_data()
{
	for (const auto texture : fish_textures) SDL_DestroyTexture(texture);
	SDL_DestroyTexture(background_texture);
}