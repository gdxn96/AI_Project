#pragma once
#include "Vector2D.h"

class Rect {
public:
	Vector2D pos;
	Vector2D size;
	Rect(Vector2D p, Vector2D s) :pos(p), size(s) {};
	Rect(float x = 0, float y = 0, float w = 1, float h = 1) :pos(x, y), size(w, h) {};
	Rect(sf::FloatRect& r) : pos(r.left, r.top), size(r.width, r.height) {}

	Rect& operator*(float scale)
	{
		return Rect(this->pos.x * scale, this->pos.y * scale, this->size.w * scale, this->size.h * scale);
	}

	Rect& operator/(float scale)
	{
		return Rect(this->pos.x / scale, this->pos.y / scale, this->size.w / scale, this->size.h / scale);
	}

	Rect& operator+(Rect& r)
	{
		return Rect(this->pos.x + r.pos.x, this->pos.y + r.pos.y, this->size.w + r.size.w, this->size.h + r.size.h);
	}

	Vector2D getCentreCopy()
	{
 		return  Vector2D(this->pos.x + this->size.w / 2, this->pos.y + this->size.h / 2);
	}

	sf::RectangleShape toSFMLRect()
	{
		sf::RectangleShape rect = sf::RectangleShape(size.toSFMLVector());
		rect.setPosition(pos.toSFMLVector());
		return rect;
	}

	bool containsPoint(Vector2D pt)
	{
		float x = pt.x;
		float y = pt.y;
		if (x >= this->pos.x && x <= this->pos.x + this->size.w &&
			y >= this->pos.y && y <= this->pos.y + this->size.h)
			return true;
		else
			return false;
	}
};