//
//  Game.cpp
//  test
//
//  Created by Jade Westover on 2/24/23.
//

#include "Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"

using namespace std;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Camera* Game::camera = nullptr;

Game::Game(const char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_VIDEO) == 0 && TTF_Init() == 0) {
		srand(static_cast<unsigned>(time(0)));
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
								  SDL_WINDOWPOS_CENTERED, width, height,
								  SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		scoreFont = TTF_OpenFont("src/resources/fonts/slkscr.ttf", 16);
		highScoreFont = TTF_OpenFont("src/resources/fonts/slkscr.ttf", 8);
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);

		float renderScaleWidth = width / Game::viewWidth;
		float renderScaleHeight = height / Game::viewHeight;
		SDL_RenderSetScale(renderer, renderScaleWidth, renderScaleHeight);
		running = true;
	} else {
		cout << "There was an error starting the game" << endl;
	}

	player = new Player("src/resources/textures/sprites/ruby.png",
						Vector2D(0.0, Game::gameFloor), Game::tileSize,
						Game::tileSize, true);
	lettuces = vector<GameObject*>();
	donuts = vector<GameObject*>();
	map = new Map();
	camera = new Camera();
}

Game::~Game() {
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(scoreFont);
	TTF_CloseFont(highScoreFont);
	SDL_Quit();
	delete player;
	delete map;
	delete camera;
}

void Game::generateBlocks(vector<GameObject*>& blocks, const char* path,
						  int numToGenerateMax, bool animated) {
	if ((int)camera->position.x % viewHeight == 0) {
		for (int i = 0; i < rand() % numToGenerateMax; i++) {
			int x = rand() % viewWidth;
			int placePosition = camera->position.x + viewWidth + x;
			auto block =
				new GameObject(path, Vector2D(placePosition, gameFloor), 16, 16,
							   gameFloor, animated);
			blocks.push_back(block);
		}
	}
}

void Game::deallocateBlocks(vector<GameObject*>& blocks) {
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i]->position.x < camera->position.x - Game::viewWidth) {
			delete blocks[i];
			blocks.erase(blocks.begin() + i);
		}
	}
}

void Game::renderScore() {
	SDL_Color color = {255, 255, 255};

	string scoreText = "Score: " + to_string(score);
	string highScoreText = "Hi-Score: " + to_string(highScore);

	SDL_Surface* scoreSurface =
		TTF_RenderText_Solid(scoreFont, scoreText.c_str(), color);

	if (scoreSurface == nullptr) {
		cerr << "Failed to create surface: " << TTF_GetError() << endl;
		TTF_CloseFont(scoreFont);
		return;
	}

	SDL_Surface* highScoreSurface =
		TTF_RenderText_Solid(highScoreFont, highScoreText.c_str(), color);

	if (highScoreSurface == nullptr) {
		cerr << "Failed to create high score surface: " << TTF_GetError()
			 << endl;
		TTF_CloseFont(highScoreFont);
		return;
	}

	SDL_Texture* scoreTexture =
		SDL_CreateTextureFromSurface(Game::renderer, scoreSurface);

	if (scoreTexture == nullptr) {
		cerr << "Failed to create texture: " << SDL_GetError() << endl;
		SDL_FreeSurface(scoreSurface);
		TTF_CloseFont(scoreFont);
		return;
	}

	SDL_Texture* highScoreTexture =
		SDL_CreateTextureFromSurface(Game::renderer, highScoreSurface);

	if (highScoreTexture == nullptr) {
		cerr << "Failed to create high score texture: " << SDL_GetError()
			 << endl;
		SDL_FreeSurface(highScoreSurface);
		TTF_CloseFont(highScoreFont);
		return;
	}

	SDL_Rect rect = {(viewWidth / 2) - (scoreSurface->w / 2), 0,
					 scoreSurface->w, scoreSurface->h};
	SDL_Rect highScoreRect = {(viewWidth / 2) - (highScoreSurface->w / 2), 16,
							  highScoreSurface->w, highScoreSurface->h};

	TextureManager::draw(scoreTexture, &rect);
	TextureManager::draw(highScoreTexture, &highScoreRect);
	SDL_FreeSurface(scoreSurface);
	SDL_FreeSurface(highScoreSurface);
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(highScoreTexture);
}

void Game::handleEvents() {
	SDL_PollEvent(&Game::event);

	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	default:
		break;
	}
}

void Game::render() {
	SDL_RenderClear(Game::renderer);
	map->drawMap();
	for (int i = 0; i < lettuces.size(); i++) {
		lettuces[i]->render();
	}
	for (int i = 0; i < donuts.size(); i++) {
		donuts[i]->render();
	}
	player->render();
	renderScore();
	SDL_RenderPresent(Game::renderer);
}

void Game::update() {
	camera->update();
	generateBlocks(lettuces, "src/resources/textures/sprites/lettuce.png", 5);
	generateBlocks(donuts, "src/resources/textures/sprites/donut.png", 5, true);

	for (int i = 0; i < lettuces.size(); i++) {
		lettuces[i]->update();
		if (player->isColliding(lettuces[i])) {
			score = 0;
		}
	}

	for (int i = 0; i < donuts.size(); i++) {
		donuts[i]->update();
		if (player->isColliding(donuts[i])) {
			score += donutScoreAddAmount;
			// delete donut and remove from vector
			delete donuts[i];
			donuts.erase(donuts.begin() + i);
		}
	}

	player->update();

	deallocateBlocks(lettuces);
	deallocateBlocks(donuts);

	score++;
	if (score > highScore) {
		highScore = score;
	}
}

bool Game::isRunning() { return running; }

void Game::run() {
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	while (isRunning()) {
		frameStart = SDL_GetTicks();

		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
}
