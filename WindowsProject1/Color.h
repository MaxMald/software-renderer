#pragma once

#define NOMINMAX
#include "Commons.h"

struct Color
{
	Color();
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

	Color operator+(const Color& color) const
	{
		return Color(
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(this->color.r) + static_cast<int>(color.color.r)))),
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(this->color.g) + static_cast<int>(color.color.g)))),
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(this->color.b) + static_cast<int>(color.color.b)))),
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(this->color.a) + static_cast<int>(color.color.a))))
		);
	}

	Color operator/(float scalar) const
	{
		return Color(
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(color.r) / static_cast<int>(scalar)))),
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(color.g) / static_cast<int>(scalar)))),
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(color.b) / static_cast<int>(scalar)))),
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(color.a) / static_cast<int>(scalar))))
		);
	}

	Color operator-(const Color& color) const;

	friend Color operator*(float scalar, const Color& color)
	{
		return Color(
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(color.color.r) * static_cast<int>(scalar)))),
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(color.color.g) * static_cast<int>(scalar)))),
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(color.color.b) * static_cast<int>(scalar)))),
			static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(color.color.a) * static_cast<int>(scalar))))
		);
	}

	union
	{
		struct
		{
			uint8_t r, g, b, a;
		};

		uint32_t rgba;
	} color;
};