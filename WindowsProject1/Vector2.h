#pragma once

#include "Commons.h"

struct Vector2
{
	float x;
	float y;

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2{ x - other.x, y - other.y };
	}
};