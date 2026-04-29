#pragma once

#define NOMINMAX
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <exception>
#include <functional>

using int8 = std::int8_t;
using uint8 = std::uint8_t;
using int16 = std::int16_t;
using uint16 = std::uint16_t;
using int32 = std::int32_t;
using uint32 = std::uint32_t;
using int64 = std::int64_t;
using uint64 = std::uint64_t;
using byte = std::uint8_t;

template<typename T>
using Vector = std::vector<T>;

namespace SAMPLE_FILTER
{
	enum E
	{
		POINT,
		LINEAR,
		ANISOTROPIC
	};
}

namespace TEXTURE_ADDRESS_MODE
{
	enum E
	{
		WRAP,			// Repeat the texture
		MIRROR,			// Mirror the texture at every integer junction
		CLAMP,			// Limit to the edge of the texture
		BORDER			// Use a border color for out-of-range texels
	};
}

namespace REGION_CODE
{
	enum E
	{
		INSIDE = 0,
		LEFT = 1,
		RIGHT = 2,
		BELOW = 4,
		ABOVE = 8
	};
}

struct Math
{
	[[nodiscard]] static float Clamp(float value, float min, float max)
	{
		return (std::max)(min, (std::min)(max, value));
	}

	[[nodiscard]] static int32 Clamp(int32 value, int32 min, int32 max)
	{
		return (std::max)(min, (std::min)(max, value));
	}

	[[nodiscard]] static float Floor(float value)
	{
		return std::floor(value);
	}
};


#pragma pack(push, 2) // Asegura que no haya relleno entre los campos, 
// puedes verlo en el Layout de la memoria que muestra el visual studio,
// anda has la prueba comentando el #pragma pack y verás la diferencia, 
// el tamaño de esta estructura sin el pack sería 16 bytes, 
// pero con el pack es de 14 bytes, que es lo correcto para un BMP

struct MY_BITMAPFILEHEADER
{
	uint16 bfType;      // Tipo de archivo, debe ser 'BM' (0x4D42)
	uint32 bfSize;      // Tamaño total del archivo en bytes
	uint16 bfReserved1; // Reservado, debe ser 0
	uint16 bfReserved2; // Reservado, debe ser 0
	uint32 bfOffBits;   // Desplazamiento desde el inicio del archivo hasta los datos de la imagen
};
#pragma pack(pop)

struct MY_BITMAPINFOHEADER
{
	uint32 bcSize;          // Tamaño del encabezado (14 bytes para BITMAPCOREHEADER)
	int32 bcWidth;         // Ancho de la imagen en píxeles
	int32 bcHeight;        // Alto de la imagen en píxeles
	uint16 bcPlanes;        // Número de planos de color, debe ser 1
	uint16 bcBitCount;      // Número de bits por píxel (1, 4, 8, 24, etc.)
};