//
//  Map.hpp
//  test
//
//  Created by Jade Westover on 2/25/23.
//

#pragma once

#include <SDL2/SDL.h>
#include <array>
#include <string>

#include "Camera.hpp"
#include "Player.hpp"

using namespace std;

class Map {
  public:
	Map();
	~Map();

	void loadMap(string mapfile);
	void drawMap();

  private:
	static const int numRows = 9;
	static const int numColumns = 20;

	SDL_Rect dest;
	SDL_Texture* textures[10];
	int width;
	int map[numRows][numColumns];
};
