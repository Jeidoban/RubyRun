#pragma once

#include <SDL2/SDL.h>

#include "Vector2D.hpp"

struct Camera {
	Camera(const Vector2D& position, const Vector2D& velocity);
	Camera();
	void update();

	Vector2D position;
	Vector2D velocity;
};