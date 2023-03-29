//
//  Map.cpp
//  test
//
//  Created by Jade Westover on 2/25/23.
//
#include "Map.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <fstream>
#include <string>

#include "Camera.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"

using namespace std;

const string mapTexturePrefix = "src/resources/textures/maptiles/";
const string mapDataPrefix = "src/resources/maps/";

Map::Map() {
	textures[0] = TextureManager::loadTexture(mapTexturePrefix + "blank.png");
	textures[1] = TextureManager::loadTexture(mapTexturePrefix + "dirt.png");
	textures[2] = TextureManager::loadTexture(mapTexturePrefix + "grass.png");
	textures[3] = TextureManager::loadTexture(mapTexturePrefix + "sky.png");
	textures[4] = TextureManager::loadTexture(mapTexturePrefix + "cloudbl.png");
	textures[5] = TextureManager::loadTexture(mapTexturePrefix + "cloudbr.png");
	textures[6] = TextureManager::loadTexture(mapTexturePrefix + "cloudtr.png");
	textures[7] = TextureManager::loadTexture(mapTexturePrefix + "cloudtl.png");
	textures[8] =
		TextureManager::loadTexture(mapTexturePrefix + "dirtgrass1.png");
	textures[9] =
		TextureManager::loadTexture(mapTexturePrefix + "dirtgrass2.png");

	loadMap(mapDataPrefix + "map1.csv");
	dest.w = dest.h = Game::tileSize;
	dest.x = dest.y = 0;
}

Map::~Map() {
	for (auto texture : textures) {
		SDL_DestroyTexture(texture);
	}
}

void Map::loadMap(string mapfile) {
	ifstream file;
	file.open(mapfile);

	char symbol = ' ';
	int currentColumn = 0;
	int currentRow = 0;

	if (file.is_open()) {
		while (file.peek() != EOF) {
			while (symbol != '\n' || file.peek() != EOF) {
				if (file) {
					symbol = file.get();
					if (isdigit(symbol)) {
						int num = int(symbol - '0');
						map[currentRow][currentColumn] = num;
						currentColumn++;
					}
				}
			}
			currentRow++;
		}
	}

	file.close();
}

void Map::drawMap() {
	int type = 0;
	int cameraX = Game::camera->position.x;

	int mapWidth = 20;
	int visibleColumns = Game::viewWidth / Game::tileSize + 2;

	int firstColumn = cameraX / Game::tileSize;
	int offsetX = cameraX % Game::tileSize;

	for (int row = 0; row < numRows; row++) {
		for (int visibleColumn = 0; visibleColumn < visibleColumns;
			 visibleColumn++) {
			int column = (firstColumn + visibleColumn) % mapWidth;
			type = map[row][column];

			dest.x = visibleColumn * Game::tileSize - offsetX;
			dest.y = row * Game::tileSize;

			TextureManager::draw(textures[type], &dest);
		}
	}
}
