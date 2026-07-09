#include "hc/utilities/hcColorUInt8.h"
#include "hc/utilities/hcColor.h"
#include "hc/utilities/hcMath.h"

namespace hc
{
  constexpr ColorUInt8 ColorUInt8::Black()
  {
    return ColorUInt8(0, 0, 0, 255);
  }

  constexpr ColorUInt8 ColorUInt8::White()
  {
    return ColorUInt8(255, 255, 255, 255);
  }

  constexpr ColorUInt8 ColorUInt8::Red()
  {
    return ColorUInt8(255, 0, 0, 255);
  }

  constexpr ColorUInt8 ColorUInt8::Green()
  {
    return ColorUInt8(0, 255, 0, 255);
  }

  constexpr ColorUInt8 ColorUInt8::Blue()
  {
    return ColorUInt8(0, 0, 255, 255);
  }

  constexpr ColorUInt8 ColorUInt8::Transparent()
  {
    return ColorUInt8(0, 0, 0, 0);
  }

  constexpr ColorUInt8::ColorUInt8() :
    r(0), g(0), b(0), a(255)
  {}

  constexpr ColorUInt8::ColorUInt8(UInt8 r, UInt8 g, UInt8 b, UInt8 a) :
    r(r), g(g), b(b), a(a)
  {}

  constexpr ColorUInt8::ColorUInt8(const Vector4<UInt8>&v) :
    r(v.x), g(v.y), b(v.z), a(v.w)
  {}
  constexpr ColorUInt8::ColorUInt8(const ColorUInt8 & color) :
    r(color.r), g(color.g), b(color.b), a(color.a)
  {}

  constexpr ColorUInt8::ColorUInt8(const Color & color)
  {
    r = static_cast<UInt8>(Math::Max(0, Math::Min(255, static_cast<Int32>(color.r * 255.0f))));
    g = static_cast<UInt8>(Math::Max(0, Math::Min(255, static_cast<Int32>(color.g * 255.0f))));
    b = static_cast<UInt8>(Math::Max(0, Math::Min(255, static_cast<Int32>(color.b * 255.0f))));
    a = static_cast<UInt8>(Math::Max(0, Math::Min(255, static_cast<Int32>(color.a * 255.0f))));
  }

  ColorUInt8 ColorUInt8::operator+(const ColorUInt8 & color) const
  {
    return ColorUInt8(
      static_cast<UInt8>(Math::Max(static_cast<UInt32>(0), Math::Min(static_cast<UInt32>(255), static_cast<UInt32>(this->r) + static_cast<UInt32>(color.r)))),
      static_cast<UInt8>(Math::Max(static_cast<UInt32>(0), Math::Min(static_cast<UInt32>(255), static_cast<UInt32>(this->g) + static_cast<UInt32>(color.g)))),
      static_cast<UInt8>(Math::Max(static_cast<UInt32>(0), Math::Min(static_cast<UInt32>(255), static_cast<UInt32>(this->b) + static_cast<UInt32>(color.b)))),
      static_cast<UInt8>(Math::Max(static_cast<UInt32>(0), Math::Min(static_cast<UInt32>(255), static_cast<UInt32>(this->a) + static_cast<UInt32>(color.a))))
    );
  }

  ColorUInt8 ColorUInt8::operator-(const ColorUInt8& color) const
  {
    return ColorUInt8(
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(this->r) - static_cast<Int32>(color.r)))),
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(this->g) - static_cast<Int32>(color.g)))),
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(this->b) - static_cast<Int32>(color.b)))),
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(this->a) - static_cast<Int32>(color.a))))
    );
  }

  ColorUInt8 ColorUInt8::operator/(float scalar) const
  {
    return ColorUInt8(
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(this->r / scalar)))),
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(this->g / scalar)))),
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(this->b / scalar)))),
      static_cast<UInt8>(Math::Max(static_cast<Int32>(0), Math::Min(static_cast<Int32>(255), static_cast<Int32>(this->a / scalar))))
    );
  }

  constexpr Color ColorUInt8::toColor() const
  {
    return Color(
      static_cast<float>(r) / 255.0f,
      static_cast<float>(g) / 255.0f,
      static_cast<float>(b) / 255.0f,
      static_cast<float>(a) / 255.0f
    );
  }
}