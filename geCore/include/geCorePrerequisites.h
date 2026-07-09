#pragma once

#include <hc/utilities/hcTypeAliases.h>
#include <hc/utilities/hcMath.h>
#include <hc/utilities/hcVector3.h>
#include <hc/utilities/hcVector2.h>
#include <hc/utilities/hcColor.h>
#include <hc/utilities/hcColorUInt8.h>

// HC POD Types
using hc::UInt8;
using hc::UInt16;
using hc::UInt32;
using hc::UInt64;
using hc::Int8;
using hc::Int16;
using hc::Int32;
using hc::Int64;
using hc::Byte;

// HC Math Types
using hc::Vector2f;
using hc::Vector3f;

// HC Color Types
using hc::Color;
using hc::ColorUInt8;

// HC Containers
using hc::Vector;

namespace ge
{
  using PixelShaderSW = std::function<hc::Color(float, float)>;

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

#pragma pack(push, 2) // Asegura que no haya relleno entre los campos, 
  // puedes verlo en el Layout de la memoria que muestra el visual studio,
  // anda has la prueba comentando el #pragma pack y verás la diferencia, 
  // el tamaño de esta estructura sin el pack sería 16 bytes, 
  // pero con el pack es de 14 bytes, que es lo correcto para un BMP

  struct MY_BITMAPFILEHEADER
  {
    UInt16 bfType;      // Tipo de archivo, debe ser 'BM' (0x4D42)
    UInt32 bfSize;      // Tamaño total del archivo en bytes
    UInt16 bfReserved1; // Reservado, debe ser 0
    UInt16 bfReserved2; // Reservado, debe ser 0
    UInt32 bfOffBits;   // Desplazamiento desde el inicio del archivo hasta los datos de la imagen
  };
#pragma pack(pop)

  struct MY_BITMAPINFOHEADER
  {
    UInt32 bcSize;          // Tamaño del encabezado (14 bytes para BITMAPCOREHEADER)
    Int32 bcWidth;         // Ancho de la imagen en píxeles
    Int32 bcHeight;        // Alto de la imagen en píxeles
    UInt16 bcPlanes;        // Número de planos de color, debe ser 1
    UInt16 bcBitCount;      // Número de bits por píxel (1, 4, 8, 24, etc.)
  };
}