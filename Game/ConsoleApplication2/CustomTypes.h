#pragma once
#include <math.h>


class Vector2D
{
public:
	float x;
	float y;
	Vector2D(float _x = 0, float _y = 0) : x(_x), y(_y) {};
	float length() { return sqrt(x * x + y * y); }

	Vector2D operator*(const Vector2D& rhs) { return Vector2D(x * rhs.x, y * rhs.y); }
	Vector2D operator*(const float& rhs) { return Vector2D(x * rhs, y * rhs); }
	bool operator==(Vector2D& rhs) { return x == rhs.x && y == rhs.y; }
	const bool operator==(const Vector2D& rhs) { return x == rhs.x && y == rhs.y; }
};


