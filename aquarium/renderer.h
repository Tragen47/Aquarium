#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <Windows.h>

extern SDL_Renderer* main_renderer;

template<typename T>
constexpr T check_for_null(T variable, const char* (*error_function)())
{
	if (!variable) {
		MessageBoxA(NULL, error_function(), NULL, MB_OK);
		exit(-1);
	}
	return variable;
}

inline SDL_Texture* load_picture(const char* path, SDL_Renderer* sdl_renderer)
{
	SDL_Surface* surface = check_for_null(IMG_Load(path), IMG_GetError);

	// load image to the SDL texture per pixel
	SDL_Texture* new_texture = check_for_null(SDL_CreateTextureFromSurface(sdl_renderer, surface), SDL_GetError);
	SDL_SetTextureBlendMode(new_texture, SDL_BLENDMODE_BLEND); // mode, which supports alpha channel

	SDL_FreeSurface(surface);
	return new_texture;
}