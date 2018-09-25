#include "menu.h"
#include <Windows.h>
#include <stdexcept>

Menu::Button::Button(SDL_Texture* texture, const int x, const int y) : texture(texture)
{
	// adjust buttons size to their textures size
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	rectangle = { x, y, w, h };
}

Menu::Menu(const SDL_Rect& window_rectangle, Aquarium& aquarium) : aquarium(aquarium)
{
	// set menu and aquarium size and coordinates
	menu_rectangle = { 0, 0, window_rectangle.w, 100 };

	// load textures for menu
	menu_buttons.emplace_back(load_picture("../textures/UI/add_pike.png", main_renderer), 50, 30);
	menu_buttons.emplace_back(load_picture("../textures/UI/add_carp.png", main_renderer), window_rectangle.w - 270, 30);

	// draw buttons
	for(const auto& button : menu_buttons)
		SDL_RenderCopy(main_renderer, button.texture, NULL, &button.rectangle);
}

inline void change_button_light(SDL_Texture* texture, const SDL_Rect& rectangle, bool& selected)
{
	selected = !selected; // invert boolean value

	// highlight/lowlight the button if the mouse is in rectangle
	SDL_SetTextureBlendMode(texture, (SDL_BlendMode)(2 * selected));
	SDL_RenderCopy(main_renderer, texture, NULL, &rectangle);
}

// check whether the mouse cursor is within a button
inline bool mouse_is_in_rectangle(const SDL_Rect& rectangle)
{
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	return mouse_x >= rectangle.x &&
		mouse_x <= rectangle.w + rectangle.x &&
		mouse_y >= rectangle.y &&
		mouse_y <= rectangle.y + rectangle.h;
}

void Menu::handle_input(const SDL_Event& e)
{
	// get the mouse cursor current position
	for (size_t i = 0; i < menu_buttons.size(); ++i)
		if (mouse_is_in_rectangle(menu_buttons[i].rectangle)) {
			if (!menu_buttons[i].selected)
				change_button_light(menu_buttons[i].texture, menu_buttons[i].rectangle, menu_buttons[i].selected);
			try {
				// if the button is pressed by LMB
				if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
					aquarium.add_fish(i); // factory pattern
			}
			catch (const std::overflow_error&) {
				MessageBoxA(NULL, "Error! Memory overflow!", NULL, MB_OK);
				exit(-1);
			}
		}
		else
			if (menu_buttons[i].selected) // if the mouse cursor has left rectangle
				change_button_light(menu_buttons[i].texture, menu_buttons[i].rectangle, menu_buttons[i].selected);
}

void Menu::free_sdl_data()
{
	for (const auto& button : menu_buttons) SDL_DestroyTexture(button.texture);
}