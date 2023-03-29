//
//  Vector2D.hpp
//  test
//
//  Created by Jade Westover on 2/26/23.
//

#pragma once

struct Vector2D {
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);
	Vector2D operator+(const Vector2D& vector) const;
	Vector2D operator-(const Vector2D& vector) const;
	Vector2D operator*(const Vector2D& vector) const;
	Vector2D operator/(const Vector2D& vector) const;
};