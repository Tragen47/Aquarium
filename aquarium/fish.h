#pragma once

#include "renderer.h"

enum class Direction : char { BACKWARD = -1, STOP, FORWARD };

class Fish {
public:
	Fish(SDL_Rect&, SDL_Texture*, const float = 2);
	void draw();

	// check whether the border is reached
	void look(bool&, bool&, const float, const float);
	void move();
private:
	SDL_Texture* texture;
	SDL_FRect fish_rectangle;
	float speed;
	SDL_Rect& borders;

	struct Directions {
		Direction x, y;
	} direction;
};