#pragma once

#include "Commons.h"

using hc::Vector3f;
using hc::Vector2f;
using hc::ColorUInt8;

struct Vertex
{
	Vector3f position;
	Vector2f uv;
	ColorUInt8 color;
};