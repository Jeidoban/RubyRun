//
//  Player.cpp
//  test
//
//  Created by Jade Westover on 2/27/23.
//

#include "Player.hpp"

#include <SDL2/SDL.h>

#include <iostream>

#include "Game.hpp"
#include "GameObject.hpp"

using namespace std;

Player::Player(const char* textureSheet, Vector2D position, int width,
			   int height, bool animated)
	: GameObject(textureSheet, position, width, height, Game::gameFloor,
				 animated),
	  isJumping(false), holdingJumpButton(false) {
	speed = Game::gameSpeed;
	gravityEnabled = true;
}

void Player::controlPlayer() {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	// Check for combinations of keys to determine player movement
	if (keystate[SDL_SCANCODE_D] && keystate[SDL_SCANCODE_W]) {
		moveHorizontal(1);
		jump();
	} else if (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_W]) {
		moveHorizontal(-1);
		jump();
	} else if (keystate[SDL_SCANCODE_D]) {
		holdingJumpButton = false;
		moveHorizontal(1);
	} else if (keystate[SDL_SCANCODE_A]) {
		holdingJumpButton = false;
		moveHorizontal(-1);
	} else if (keystate[SDL_SCANCODE_W]) {
		jump();
	} else {
		holdingJumpButton = false;
		velocity.x = speed;
	}

	// If player is above the floor, set isJumping to false
	if (position.y > floor)
		isJumping = false;

	// If player is less than or equal to the left side of the screen, set
	// rect.x to 0
	if (rect.x <= 0) {
		rect.x = 0;
		position.x = Game::camera->position.x;
	}

	// If player is greater than or equal to the right side of the screen, set
	// rect.x to the right side of the screen
	if (rect.x >= Game::viewWidth - rect.w) {
		rect.x = Game::viewWidth - rect.w;
		position.x = Game::camera->position.x + Game::viewWidth - rect.w;
	}
}
// Method that moves the player horizontally
void Player::moveHorizontal(int multiplier) {
	position.x += speedMultiplier * multiplier;
	rect.x += speedMultiplier * multiplier;
}

// Method that updates the player
void Player::update() {
	controlPlayer();
	// If the player is jumping, set the animation frame to the jump frame
	if (isAnimated) {
		if (isJumping) {
			animationFrame = 3;
			srcRect.x = srcRect.w * animationFrame;
		} else {
			animate();
		}
	}

	if (gravityEnabled)
		applyGravity();

	position.x += velocity.x;
	position.y += velocity.y;

	rect.y = position.y;
}

void Player::jump() {
	// If the player isn't holding the jump button, initiate a jump
	if (!holdingJumpButton) {
		holdingJumpButton = true;
		if (!isJumping) {
			// Adjust player position and velocity to initiate a jump
			position.y -= 1;
			velocity.y = jumpVelocity;
			isJumping = true;
		}
	}
}

// The below method isn't being used because I need to finish this project and
// move onto other things. Originally I was going to use this method to
// determine if the player was colliding with a platform, but I ended up nixing
// that idea and just kept everything on the same plane. Maybe I'll come back to
// this and finish it later.

// Method that determines the current ground position of the player based on
// collisions with objects
void Player::setIntersectingGroundPos(GameObject* object) {
	SDL_Rect temp = this->rect;
	// Create a temporary rectangle to check for collisions with the floor.
	// Adding +1 so SDL can detect collision. Adding velocity to check if
	// next frame position is below the floor and if so, trigger collision
	// so weird below floor frame isn't rendered.
	temp.y += velocity.y + 1;
	bool isColliding = SDL_HasIntersection(&temp, &object->rect);

	// If there is a collision and the player is above the object, set the floor
	// to the top of the object
	if (isColliding && (rect.y < object->rect.y - (rect.h / 2))) {
		floor = object->rect.y - rect.h;
		currentlyCollidingObject = object;
	} else {
		// If there is no collision or the player is below the object, set the
		// floor to the default game floor
		if (currentlyCollidingObject == object) {
			floor = Game::gameFloor;
			currentlyCollidingObject = nullptr;
		}
	}
}
