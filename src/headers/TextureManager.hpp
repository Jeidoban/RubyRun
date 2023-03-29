//
//  TextureManager.hpp
//  test
//
//  Created by Jade Westover on 2/25/23.
//

#pragma once

#include <SDL2/SDL.h>

#include <string>

using namespace std;

class TextureManager {
  public:
	static SDL_Texture* loadTexture(string fileName);
	static void draw(SDL_Texture* texture, const SDL_Rect* dest,
					 const SDL_Rect* src = nullptr);
};
