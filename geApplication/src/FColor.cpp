#include "FColor.h"

FColor::FColor(const Color& color) : 
	r(color.color.r / 255.0f), 
	g(color.color.g / 255.0f), 
	b(color.color.b / 255.0f), 
	a(color.color.a / 255.0f)
{
}

FColor::FColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
{
}

FColor FColor::operator*(float scalar) const
{
	return FColor(r * scalar, g * scalar, b * scalar, a * scalar);
}

FColor FColor::operator+(const FColor& other) const
{
	return FColor(r + other.r, g + other.g, b + other.b, a + other.a);
}

Color FColor::ToColor() const
{
	return Color(
		static_cast<uint8_t>(Math::Clamp(r * 255.0f, 0.0f, 255.0f)),
		static_cast<uint8_t>(Math::Clamp(g * 255.0f, 0.0f, 255.0f)),
		static_cast<uint8_t>(Math::Clamp(b * 255.0f, 0.0f, 255.0f)),
		static_cast<uint8_t>(Math::Clamp(a * 255.0f, 0.0f, 255.0f))
	);
}