#pragma once

#include "hc/utilities/hcUtilitiesPrerequisites.h"
#include "hc/utilities/hcVector4.h"

namespace hc
{
  /**
   * @brief Represents a color with red, green, blue, and alpha components in
   * floating-point format. The components are typically in the range [0.0, 1.0].
   */
  struct Color
  {
    union
    {
      float m[4];
      struct { float r, g, b, a; };
      Vector4f vec4;
    };

    static constexpr Color Black();
    static constexpr Color White();
    static constexpr Color Red();
    static constexpr Color Green();
    static constexpr Color Blue();
    static constexpr Color Transparent();

    static inline Color Lerp(const Color& a, const Color& b, float t);

    constexpr Color();
    constexpr Color(float r, float g, float b, float a = 1.0f);
    constexpr Color(const Vector4f& v);

    constexpr bool operator==(const Color& rhs) const;
    constexpr bool operator!=(const Color& rhs) const;

    constexpr Vector4f toVector() const;

    void clamp();
  };

  constexpr Color Color::Black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
  constexpr Color Color::White() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
  constexpr Color Color::Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
  constexpr Color Color::Green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
  constexpr Color Color::Blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
  constexpr Color Color::Transparent() { return Color(0.0f, 0.0f, 0.0f, 0.0f); }

  inline Color Color::Lerp(const Color& a, const Color& b, float t)
  {
    return Color(
      a.r + (b.r - a.r) * t,
      a.g + (b.g - a.g) * t,
      a.b + (b.b - a.b) * t,
      a.a + (b.a - a.a) * t
    );
  }

  constexpr Color::Color()
    : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {
  }

  constexpr Color::Color(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a) {
  }

  constexpr Color::Color(const Vector4f& v)
    : r(v.x), g(v.y), b(v.z), a(v.w) {
  }

  constexpr bool Color::operator==(const Color& rhs) const
  {
    return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
  }

  constexpr bool Color::operator!=(const Color& rhs) const
  {
    return !(*this == rhs);
  }

  constexpr Vector4f Color::toVector() const
  {
    return Vector4f(r, g, b, a);
  }

  inline void Color::clamp()
  {
    r = (r < 0.0f) ? 0.0f : (r > 1.0f) ? 1.0f : r;
    g = (g < 0.0f) ? 0.0f : (g > 1.0f) ? 1.0f : g;
    b = (b < 0.0f) ? 0.0f : (b > 1.0f) ? 1.0f : b;
    a = (a < 0.0f) ? 0.0f : (a > 1.0f) ? 1.0f : a;
  }
}
