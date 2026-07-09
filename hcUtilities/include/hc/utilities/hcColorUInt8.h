#pragma once

#include "hc/utilities/hcUtilitiesPrerequisites.h"
#include "hc/utilities/hcVector4.h"
#include "hc/utilities/hcMath.h"

namespace hc
{
  struct Color;

  /**
   * @brief Represents a color with red, green, blue, and alpha components in
   * unsigned 8-bit integer format. The components are typically in the range [0, 255].
   */
  struct HC_UTILITY_EXPORT ColorUInt8
  {
    static constexpr ColorUInt8 Black();
    static constexpr ColorUInt8 White();
    static constexpr ColorUInt8 Red();
    static constexpr ColorUInt8 Green();
    static constexpr ColorUInt8 Blue();
    static constexpr ColorUInt8 Transparent();

    union
    {
      UInt8 m[4];
      UInt32 rgba;
      struct {
        UInt8 r;
        UInt8 g;
        UInt8 b;
        UInt8 a;
      };
      Vector4<UInt8> vec4;
    };

    constexpr ColorUInt8();
    constexpr ColorUInt8(UInt8 r, UInt8 g, UInt8 b, UInt8 a = 255);
    constexpr ColorUInt8(const Vector4<UInt8>& v);
    constexpr ColorUInt8(const ColorUInt8& color);
    explicit constexpr ColorUInt8(const Color& color);

    ColorUInt8 operator+(const ColorUInt8& color) const;
    ColorUInt8 operator-(const ColorUInt8& color) const;
    ColorUInt8 operator/(float scalar) const;
    friend ColorUInt8 operator*(float scalar, const ColorUInt8& color);
    constexpr Color toColor() const;
  };

  inline ColorUInt8 operator*(float scalar, const ColorUInt8& color)
  {
    return ColorUInt8(
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(color.r * scalar)))),
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(color.g * scalar)))),
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(color.b * scalar)))),
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(color.a * scalar))))
    );
  }
}