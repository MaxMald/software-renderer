#pragma once

#include "geCorePrerequisites.h"
#include "geTriangle.h"

namespace ge
{
  class Image
  {
  public:
    Image();
    ~Image() = default;

    void create(Int32 w, Int32 h, Int32 bpp);
    void load(const char* filename);
    void unload();
    void clear(const ColorUInt8& color);
    void setPixel(Int32 x, Int32 y, const ColorUInt8& color);
    ColorUInt8 getPixel(Int32 x, Int32 y) const;
    Int32 computeRegionCode(Int32 x, Int32 y, Int32 xMin, Int32 yMin, Int32 xMax, Int32 yMax) const;

    /**
     * Clips a line defined by the endpoints (x0, y0) and (x1, y1)
     * against the boundaries of the image. The function modifies the endpoints of the
     * line to fit within the image boundaries.
     */
    bool clipLine(Int32& x0, Int32& y0, Int32& x1, Int32& y1) const;
    void line(Int32 x0, Int32 y0, Int32 x1, Int32 y1, const ColorUInt8& color);
    void bressenhamLine(Int32 x0, Int32 y0, Int32 x1, Int32 y1, const ColorUInt8& color);
    void bressehamCircle(Int32 centerX, Int32 centerY, Int32 radius, const ColorUInt8& color);
    void bitBlt(Int32 x, Int32 y, const Image& src);
    void drawTriangle(
      Int32 x0,
      Int32 y0,
      Int32 x1,
      Int32 y1,
      Int32 x2,
      Int32 y2,
      const ColorUInt8& color
    );

    void drawFilledTriangle(
      const Triangle& triangle,
      const PixelShaderSW& pixelShader
    );

    void drawBottomTriangle(
      const Triangle& triangle,
      const PixelShaderSW& pixelShader
    );

    void drawTopTriangle(
      const Triangle& triangle,
      const PixelShaderSW& pixelShader
    );

    Int32 getWidth() const { return m_width; }
    Int32 getHeight() const { return m_height; }
    Int32 getBPP() const { return m_bpp; }
    Int32 getPitch() const { return m_width * getBytesPerPixel(); }
    Int32 getBytesPerPixel() const { return m_bpp >> 3; } // >> 3 is the same as / 8
    Byte* getData() { return m_data.data(); }

  private:
    Int32 m_width;
    Int32 m_height;
    Int32 m_bpp;
    Vector<Byte> m_data;
  };
}