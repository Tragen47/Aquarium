#pragma once

#include "fish.h"
#include "aquarium.h"

Fish::Fish(SDL_Rect& borders, SDL_Texture* texture, const float speed) :
	borders(borders), texture(texture),
	speed(speed), direction({ Direction::FORWARD, Direction::STOP })
{
	int width, height;
	if (SDL_QueryTexture(texture, NULL, NULL, &width, &height) < 0) {
		MessageBoxA(NULL, SDL_GetError(), NULL, MB_OK);
		exit(-1);
	}
	fish_rectangle = { (float)(std::rand() % (borders.w - width - 1) + borders.x),
		(float)(std::rand() % (borders.h - height - 1) + borders.y), (float)width, (float)height };
}

void Fish::draw()
{
	SDL_FPoint fish_back = { 0, fish_rectangle.h / 2 };

	// direct the fish texture towards its movement direction
	SDL_RenderCopyExF(main_renderer, texture, NULL,
		&fish_rectangle,
		(bool)direction.x ? 0 : 90 * (int)direction.y,
		&fish_back, (SDL_RendererFlip)(direction.x == Direction::BACKWARD));
}

void Fish::look(bool& is_on_x, bool& is_on_y, const float shift_x, const float shift_y)
{
	is_on_x =
		// right border
		fish_rectangle.x + fish_rectangle.w + shift_x >= borders.x + borders.w ||

		// left border
		fish_rectangle.x + shift_x <= borders.x;

	is_on_y =
		// lower border
		fish_rectangle.y + ((bool)direction.x ? fish_rectangle.h :
		(direction.y == Direction::FORWARD) * fish_rectangle.w) + shift_y >= borders.y + borders.h ||
		
		// upper border
		fish_rectangle.y - (!(bool)direction.x && direction.y != Direction::FORWARD) *
		fish_rectangle.w + shift_y <= borders.y;
}

void Fish::move()
{
	bool is_border_on_x = false, is_border_on_y = false;

	float speed_modifier = (char)direction.x && (char)direction.y ? sqrtf(2) : 1;

	float shift_x = (float)direction.x * speed / speed_modifier;
	float shift_y = (float)direction.y * speed / speed_modifier;

	look(is_border_on_x, is_border_on_y, shift_x, shift_y);

	if (is_border_on_x || is_border_on_y) {
		direction = { (Direction)(is_border_on_x ? -(signed char)direction.x : (rand() % 3) - 1),
			(Direction)(is_border_on_y ? -(signed char)direction.y : (rand() % 3) - 1) };

		speed_modifier = (bool)direction.x && (bool)direction.y ? sqrtf(2) : 1;

		shift_x = (float)direction.x * speed / speed_modifier;
		shift_y = (float)direction.y * speed / speed_modifier;
	}

	fish_rectangle.x += shift_x;
	fish_rectangle.y += shift_y;
}