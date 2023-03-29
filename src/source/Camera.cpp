#include "Camera.hpp"
#include "Game.hpp"

using namespace std;

Camera::Camera(const Vector2D& position, const Vector2D& velocity)
	: position(position), velocity(velocity) {}
Camera::Camera()
	: position(Vector2D(0, 0)), velocity(Vector2D(Game::gameSpeed, 0)){}

void Camera::update() {
	position.x += velocity.x;
	position.y += velocity.y;
}
