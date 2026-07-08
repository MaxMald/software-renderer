#pragma once

#include "Commons.h"
#include "Color.h"
#include "Vertex.h"

struct FColor
{
	FColor() = default;
	explicit FColor(const Color& color);
	FColor(float r, float g, float b, float a = 1.0f);

	FColor operator*(float scalar) const;
	FColor operator+(const FColor& other) const;

	Color ToColor() const;

	float r;
	float b;
	float g;
	float a;
};

inline FColor Lerp(const FColor& a, const FColor& b, float t)
{
	return FColor(
		a.r + (b.r - a.r) * t,
		a.g + (b.g - a.g) * t,
		a.b + (b.b - a.b) * t,
		a.a + (b.a - a.a) * t
	);
}

using PixelShaderSW = std::function<FColor(float, float)>;