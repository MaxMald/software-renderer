#include "Color.h"

Color::Color() : color{ 0, 0, 0, 255 }
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : color{ r, g, b, a }
{
}

Color Color::operator-(const Color& color) const
{
	return Color(
		static_cast<uint8_t>(std::max(0, static_cast<int>(this->color.r) - static_cast<int>(color.color.r))),
		static_cast<uint8_t>(std::max(0, static_cast<int>(this->color.g) - static_cast<int>(color.color.g))),
		static_cast<uint8_t>(std::max(0, static_cast<int>(this->color.b) - static_cast<int>(color.color.b))),
		static_cast<uint8_t>(std::max(0, static_cast<int>(this->color.a) - static_cast<int>(color.color.a)))
	);
}
