//
//  Player.hpp
//  test
//
//  Created by Jade Westover on 2/27/23.
//

#pragma once

#include <stdio.h>

#include "GameObject.hpp"

class Player : public GameObject {
  public:
	Player(const char* textureSheet, Vector2D position, int width, int height,
		   bool animated = false);
	void setIntersectingGroundPos(GameObject* object);
	void update() override;

  private:
	bool isJumping;
	bool holdingJumpButton;
	GameObject* currentlyCollidingObject = nullptr;

	const int speedMultiplier = 3;
	const float jumpVelocity = -6.0;

	void controlPlayer();
	void jump();
	void moveHorizontal(int multiplier);
};
