#pragma once

#include "Commons.h"

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3 operator-(const Vector3& other) const
	{
		return Vector3{ x - other.x, y - other.y, z - other.z };
	}

	Vector3 operator+(const Vector3& other) const
	{
		return Vector3{ x + other.x, y + other.y, z + other.z };
	}
};