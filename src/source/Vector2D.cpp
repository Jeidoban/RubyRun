//
//  Vector2D.cpp
//  test
//
//  Created by Jade Westover on 2/26/23.
//

#include "Vector2D.hpp"

Vector2D::Vector2D() : x(0), y(0) {}
Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

Vector2D Vector2D::operator+(const Vector2D& secondVector) const {
	Vector2D vector;
	vector.x = this->x + secondVector.x;
	vector.y = this->y + secondVector.y;
	return vector;
}

Vector2D Vector2D::operator-(const Vector2D& secondVector) const {
	Vector2D vector;
	vector.x = this->x - secondVector.x;
	vector.y = this->y - secondVector.y;
	return vector;
}

Vector2D Vector2D::operator*(const Vector2D& secondVector) const {
	Vector2D vector;
	vector.x = this->x * secondVector.x;
	vector.y = this->y * secondVector.y;
	return vector;
}

Vector2D Vector2D::operator/(const Vector2D& secondVector) const {
	Vector2D vector;
	vector.x = this->x / secondVector.x;
	vector.y = this->y / secondVector.y;
	return vector;
}
