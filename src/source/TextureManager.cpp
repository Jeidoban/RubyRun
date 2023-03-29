//
//  TextureManager.cpp
//  test
//
//  Created by Jade Westover on 2/25/23.
//

#include "TextureManager.hpp"

#include <SDL2_image/SDL_image.h>

#include <string>

#include "Game.hpp"

using namespace std;

SDL_Texture* TextureManager::loadTexture(string filename) {
	const char* cstrFilename = filename.c_str();
	return IMG_LoadTexture(Game::renderer, cstrFilename);
}

void TextureManager::draw(SDL_Texture* texture, const SDL_Rect* dest,
						  const SDL_Rect* src) {
	SDL_RenderCopy(Game::renderer, texture, src, dest);
}
