//
//  GameObject.hpp
//  test
//
//  Created by Jade Westover on 2/25/23.
//

#pragma once

#include <SDL2/SDL.h>

#include "Vector2D.hpp"

class GameObject {
  public:
	GameObject(const char* textureName);
	GameObject(const char* textureName, const Vector2D& position, int width,
			   int height, int floor = -1, bool animated = false);
	~GameObject();

	virtual void update();
	void render();
	bool isColliding(GameObject* other);
	void applyGravity();
	void animate();

	Vector2D position;
	Vector2D velocity;
	SDL_Rect rect;
	SDL_Rect srcRect;

  protected:
	const int spriteAnimationFrames = 4;

	bool isAnimated = false;
	int animationFrame = 0;
	bool gravityEnabled = false;
	float gravity = 0.4;
	float speed = 1.25;
	int floor;

	SDL_Texture* objTexture;
};
