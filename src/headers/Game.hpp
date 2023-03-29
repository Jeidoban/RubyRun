//
//  Game.hpp
//  test
//
//  Created by Jade Westover on 2/24/23.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <vector>

#include "Camera.hpp"
#include "Map.hpp"
#include "Player.hpp"

using namespace std;

class Game {
  private:
	SDL_Window* window;
	bool running;
	Map* map;
	Player* player;
	TTF_Font* scoreFont;
	TTF_Font* highScoreFont;
	vector<GameObject*> lettuces;
	vector<GameObject*> donuts;
	int score = 0;
	int highScore = 0;
	int donutScoreAddAmount = 200;

	void handleEvents();
	void render();
	void update();
	void generateBlocks(vector<GameObject*>& blocks, const char* path,
						int numToGenerate, bool animated = false);
	void deallocateBlocks(vector<GameObject*>& blocks);
	void renderScore();

  public:
	const static int viewWidth = 240;
	const static int viewHeight = 135;
	const static int tileSize = 16;
	const static int gameFloor = tileSize * 5;
	const static float gameSpeed = 2.0;
	const static int FPS = 60;

	static Camera* camera;
	static SDL_Renderer* renderer;
	static SDL_Event event;

	Game(const char* title, int width, int height);
	~Game();
	bool isRunning();
	void run();
};
