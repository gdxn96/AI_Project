#pragma once

#include "CustomTypes.h"


class Constants
{
public:
	static const Vector2D UP;
	static const Vector2D LEFT;
	static const Vector2D DOWN;
	static const Vector2D RIGHT;
};


const Vector2D Constants::UP = Vector2D(0, -1);
const Vector2D Constants::LEFT = Vector2D(-1, 0);
const Vector2D Constants::DOWN = Vector2D(0, 1);
const Vector2D Constants::RIGHT = Vector2D(1, 0);