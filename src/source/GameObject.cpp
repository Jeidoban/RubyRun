//
//  GameObject.cpp
//  test
//
//  Created by Jade Westover on 2/25/23.
//

#include "GameObject.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Camera.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "Vector2D.hpp"

// Constructor with only the texture name
GameObject::GameObject(const char* textureName) {
	objTexture = TextureManager::loadTexture(textureName);
	position = velocity = Vector2D(0.0, 0.0);
	rect.w = rect.h = srcRect.w = srcRect.h = Game::tileSize;
	rect.x = position.x;
	rect.y = position.y;
	floor = position.y;
}

// Constructor with position, width, height, and optional floor
GameObject::GameObject(const char* textureName, const Vector2D& position,
					   int width, int height, int floor, bool animated) {
	objTexture = TextureManager::loadTexture(textureName);
	this->position = position;
	velocity = Vector2D(0.0, 0.0);
	rect.w = srcRect.w = width;
	rect.h = srcRect.h = height;
	rect.x = position.x;
	rect.y = position.y;
	isAnimated = animated;
	this->floor = (floor == -1) ? position.y : floor;
}

GameObject::~GameObject() { SDL_DestroyTexture(objTexture); }

// Update function that applies gravity and updates position and rectangle
void GameObject::update() {
	if (gravityEnabled)
		applyGravity();
	if (isAnimated) {
		animate();
	}

	position.x += velocity.x;
	position.y += velocity.y;

	// rect.x needs to be relative to the camera position
	rect.x = position.x - Game::camera->position.x;
	rect.y = position.y;
}

// Animate object that has 4 tile sprite sheet
void GameObject::animate() {
	animationFrame = static_cast<int>((SDL_GetTicks() / 100) % spriteAnimationFrames);
	srcRect.x = srcRect.w * animationFrame;
	srcRect.y = 0;
	srcRect.w = rect.w;
	srcRect.h = rect.h;
}

// Render the object to the screen
void GameObject::render() { TextureManager::draw(objTexture, &rect, &srcRect); }

// method that determines if gameobject is colliding with another object using
// SDL
bool GameObject::isColliding(GameObject* other) {
	if (SDL_HasIntersection(&rect, &other->rect)) {
		return true;
	}
	return false;
}

// Apply gravity to the object
void GameObject::applyGravity() {
	if (position.y + velocity.y > floor) {
		// If the player will be below the floor in the next frame, stop it and
		// set it to the floor position
		velocity.y = 0.0;
		position.y = floor;
	} else {
		// Otherwise, apply gravity to the velocity
		velocity.y += gravity;
	}
}
