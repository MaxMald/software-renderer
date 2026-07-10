#include "ge/assets/geImage.h"

#include <fstream>
#include <iostream>

using std::ios;

#include "ge/graphics/geTriangle.h"

namespace ge
{
  Image::Image() : m_width(0), m_height(0), m_bpp(0)
  {}

  void Image::create(Int32 w, Int32 h, Int32 bpp)
  {
    unload();
    m_width = w;
    m_height = h;
    m_bpp = bpp;
    m_data.resize(m_width * m_height * getBytesPerPixel());
  }

  void Image::load(const char* filename)
  {
    std::fstream imgFile(filename, std::ios::in | std::ios::binary | std::ios::ate);
    if (!imgFile.is_open())
    {
      return;
    }

    auto fileSize = imgFile.tellg();
    imgFile.seekg(0, std::ios::beg);

    MY_BITMAPFILEHEADER fileHeader;
    imgFile.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

    if (fileHeader.bfType != 0x4D42) // 'BM' in little-endian
    {
      std::cerr << "Error: El archivo no es un BMP válido." << std::endl;
      return;
    }

    MY_BITMAPINFOHEADER coreInfoHeader;
    imgFile.read(reinterpret_cast<char*>(&coreInfoHeader), sizeof(coreInfoHeader));

    if (coreInfoHeader.bcBitCount != 24 && coreInfoHeader.bcBitCount != 32)
    {
      std::cerr << "Error: Solo se soportan BMP de 24 o 32 bits." << std::endl;
      imgFile.close();
      return;
    }

    create(coreInfoHeader.bcWidth, coreInfoHeader.bcHeight, coreInfoHeader.bcBitCount);
    imgFile.seekg(fileHeader.bfOffBits, std::ios::beg);

    Int32 padding = getPitch() % 4;
    Int32 lineMemoryWidth = getPitch();

    if (padding > 0)
    {
      padding = 4 - padding;
      lineMemoryWidth += padding;
    }

    // invertir lineas, bmp guarda las lineas de abajo hacia arriba

    for (Int32 line = m_height - 1; line >= 0; --line)
    {
      imgFile.seekg(line * lineMemoryWidth + fileHeader.bfOffBits);
      imgFile.read(reinterpret_cast<char*>(&m_data[getPitch() * (m_height - 1 - line)]), getPitch());
    }

    // convertir de BGR a RGB
    for (Int32 i = 0; i < m_width * m_height; ++i)
    {
      UInt32 offset = i * getBytesPerPixel();
      std::swap(m_data[offset], m_data[offset + 2]);
    }

    imgFile.close();
    std::cout << "BMP cargado exitosamente: " << filename << " (" << m_width << "x" << m_height << ", " << m_bpp << " bpp)" << std::endl;
    return;
  }

  void Image::unload()
  {
    m_width = 0;
    m_height = 0;
    m_bpp = 0;
    m_data.clear();
  }

  void Image::clear(const ColorUInt8& color)
  {
    if (getBytesPerPixel() == 4)
    {
      UInt32* pData = reinterpret_cast<UInt32*>(m_data.data());
      for (Int32 i = 0; i < m_width * m_height; ++i)
      {
        pData[i] = color.rgba;
      }
      return;
    }

    for (Int32 i = 0; i < m_width * m_height; ++i)
    {
      UInt32 offset = i * getBytesPerPixel();
      m_data[offset] = color.r;
      m_data[offset + 1] = color.g;
      m_data[offset + 2] = color.b;
    }
  }

  void Image::setPixel(Int32 x, Int32 y, const ColorUInt8& color)
  {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
      return;

    Int32 index = (y * m_width + x) * getBytesPerPixel();
    if (getBytesPerPixel() == 4)
    {
      UInt32* pData = reinterpret_cast<UInt32*>(m_data.data());
      pData[y * m_width + x] = color.rgba;
    }
  }

  ColorUInt8 Image::getPixel(Int32 x, Int32 y) const
  {
    assert(x >= 0 && x < m_width && y >= 0 && y < m_height);

    ColorUInt8 color;
    UInt32 offset = (y * m_width + x) * getBytesPerPixel();
    color.r = m_data[offset];
    color.g = m_data[offset + 1];
    color.b = m_data[offset + 2];
    color.a = (getBytesPerPixel() == 4) ? m_data[offset + 3] : 255;

    return color;
  }

  Int32 Image::computeRegionCode(
    Int32 x, Int32 y,
    Int32 xMin, Int32 yMin,
    Int32 xMax, Int32 yMax
  ) const
  {
    Int32 codeRegion = REGION_CODE::INSIDE;

    if (x < xMin)
      codeRegion |= REGION_CODE::LEFT;
    else if (x > xMax)
      codeRegion |= REGION_CODE::RIGHT;

    if (y < yMin)
      codeRegion |= REGION_CODE::BELOW;
    else if (y > yMax)
      codeRegion |= REGION_CODE::ABOVE;

    return codeRegion;
  }

  bool Image::clipLine(Int32& x0, Int32& y0, Int32& x1, Int32& y1) const
  {
    const Int32 xMin = 0;
    const Int32 yMin = 0;
    const Int32 xMax = m_width - 1;
    const Int32 yMax = m_height - 1;

    Int32 code0 = computeRegionCode(x0, y0, xMin, yMin, xMax, yMax);
    Int32 code1 = computeRegionCode(x1, y1, xMin, yMin, xMax, yMax);

    while (true)
    {
      if (!(code0 | code1)) // Two points are inside the image
      {
        return true; // The line is accepted
      }
      else if (code0 & code1) // Both points share an outside zone
      {
        return false; // The line is rejected
      }

      Int32 x = 0, y = 0;
      Int32 codeOut = code0 ? code0 : code1;

      if (codeOut & REGION_CODE::ABOVE)
      {
        x = x0 + (x1 - x0) * (yMax - y0) / (y1 - y0);
        y = yMax;
      }
      else if (codeOut & REGION_CODE::BELOW)
      {
        x = x0 + (x1 - x0) * (yMin - y0) / (y1 - y0);
        y = yMin;
      }
      else if (codeOut & REGION_CODE::RIGHT)
      {
        y = y0 + (y1 - y0) * (xMax - x0) / (x1 - x0);
        x = xMax;
      }
      else if (codeOut & REGION_CODE::LEFT)
      {
        y = y0 + (y1 - y0) * (xMin - x0) / (x1 - x0);
        x = xMin;
      }

      if (codeOut == code0)
      {
        x0 = x;
        y0 = y;
        code0 = computeRegionCode(x0, y0, xMin, yMin, xMax, yMax);
      }
      else
      {
        x1 = x;
        y1 = y;
        code1 = computeRegionCode(x1, y1, xMin, yMin, xMax, yMax);
      }
    }
  }

  void Image::line(Int32 x0, Int32 y0, Int32 x1, Int32 y1, const ColorUInt8& color)
  {
    if (!clipLine(x0, y0, x1, y1))
      return;

    float dx = static_cast<float>(x1 - x0);
    float dy = static_cast<float>(y1 - y0);

    float steps = std::max(std::abs(dx), std::abs(dy));

    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = static_cast<float>(x0);
    float y = static_cast<float>(y0);

    for (Int32 i = 0; i <= steps; ++i)
    {
      setPixel(
        static_cast<Int32>(std::round(x)),
        static_cast<Int32>(std::round(y)),
        color
      );

      x += xInc;
      y += yInc;
    }
  }

  void Image::bressenhamLine(Int32 x0, Int32 y0, Int32 x1, Int32 y1, const ColorUInt8& color)
  {
    if (!clipLine(x0, y0, x1, y1))
      return;

    Int32 dx = std::abs(x1 - x0);
    Int32 dy = std::abs(y1 - y0);

    // Determine the direction of the line
    Int32 sx = (x0 < x1) ? 1 : -1;
    Int32 sy = (y0 < y1) ? 1 : -1;

    Int32 err = dx - dy;
    Int32 err2;

    while (true)
    {
      setPixel(x0, y0, color);

      if (x0 == x1 && y0 == y1)
        break;

      err2 = err * 2;
      if (err2 > -dy)
      {
        err -= dy;
        x0 += sx;
      }
      if (err2 < dx)
      {
        err += dx;
        y0 += sy;
      }
    }
  }

  void Image::bressehamCircle(
    Int32 centerX,
    Int32 centerY,
    Int32 radius,
    const ColorUInt8& color
  )
  {
    Int32 x = radius;
    Int32 y = 0;
    Int32 err = 0;

    while (x >= y)
    {
      setPixel(centerX + x, centerY + y, color);
      setPixel(centerX + y, centerY + x, color);
      setPixel(centerX - y, centerY + x, color);
      setPixel(centerX - x, centerY + y, color);
      setPixel(centerX - x, centerY - y, color);
      setPixel(centerX - y, centerY - x, color);
      setPixel(centerX + y, centerY - x, color);
      setPixel(centerX + x, centerY - y, color);

      if (err <= 0) // This condition is separate to allow for circles with a radius of 1 pixel
      {
        ++y;
        err += 2 * y + 1;
      }
      if (err > 0) // This condition is separate to allow for circles with a radius of 1 pixel
      {
        --x;
        err -= 2 * x + 1;
      }
    }
  }

  void Image::bitBlt(Int32 x, Int32 y, const Image& src)
  {
    // TODO
  }

  void Image::drawTriangle(
    Int32 x0,
    Int32 y0,
    Int32 x1,
    Int32 y1,
    Int32 x2,
    Int32 y2,
    const ColorUInt8& color
  )
  {
    bressenhamLine(x0, y0, x1, y1, color);
    bressenhamLine(x1, y1, x2, y2, color);
    bressenhamLine(x2, y2, x0, y0, color);
  }

  void Image::drawFilledTriangle(
    const Triangle& triangle,
    const PixelShaderSW& pixelShader
  )
  {
    // Ordernarlos por su coordenada y, de menor a mayor
    Vertex v0 = triangle.v0;
    Vertex v1 = triangle.v1;
    Vertex v2 = triangle.v2;

    if (v0.position.y > v1.position.y)
      std::swap(v0, v1);
    if (v0.position.y > v2.position.y)
      std::swap(v0, v2);
    if (v1.position.y > v2.position.y)
      std::swap(v1, v2);

    // Si algunos de los vértices tienen la misma coordenada y, entonces el triángulo 
    // es plano por arriba o por abajo, y se puede rasterizar fácilmente con un solo 
    // bucle for

    if (v1.position.y == v2.position.y) // triangulo de fondo plano
    {
      drawBottomTriangle({ v0, v1, v2 }, pixelShader);
    }
    else if (v0.position.y == v1.position.y) // triangulo de techo plano
    {
      drawTopTriangle({ v0, v1, v2 }, pixelShader);
    }
    else
    {
      // El triángulo es general, lo dividimos en dos planos, uno con fondo plano y 
      // otro con techo plano

      Vertex v3;
      v3.position.x = v0.position.x + (Int32)(0.5f + ((v1.position.y - v0.position.y) *
        (v2.position.x - v0.position.x)) /
        (v2.position.y - v0.position.y));

      v3.position.y = v1.position.y;

      v3.uv.x = v0.uv.x + ((v1.position.y - v0.position.y) *
        (v2.uv.x - v0.uv.x)) /
        (v2.position.y - v0.position.y);

      v3.uv.y = v0.uv.y + ((v1.position.y - v0.position.y) *
        (v2.uv.y - v0.uv.y)) /
        (v2.position.y - v0.position.y);

      v3.color = v0.color + ((v1.position.y - v0.position.y) *
        (v2.color - v0.color)) /
        (v2.position.y - v0.position.y);

      drawBottomTriangle({ v0, v1, v3 }, pixelShader);
      drawTopTriangle({ v1, v3, v2 }, pixelShader);
    }
  }

  void Image::drawBottomTriangle(
    const Triangle& triangle,
    const PixelShaderSW& pixelShader
  )
  {
    Vertex v0 = triangle.v0;
    Vertex v1 = triangle.v1;
    Vertex v2 = triangle.v2;

    // asegurate que v1 y v2 estén ordenados por su coordenada x, de menor a mayor, 
    // para facilitar el rasterizado. Osea 2 a la izquierda y 3 a la derecha
    if (v1.position.x > v2.position.x)
      std::swap(v1, v2);

    Int32 height = static_cast<Int32>(v1.position.y - v0.position.y);
    if (height == 0) // triangulo degenerado, no se pinta 
      return;

    float dx_left = (v1.position.x - v0.position.x) / height;
    float dx_right = (v2.position.x - v0.position.x) / height;

    float du_left = (v1.uv.x - v0.uv.x) / height;
    float du_right = (v2.uv.x - v0.uv.x) / height;
    float dv_left = (v1.uv.y - v0.uv.y) / height;
    float dv_right = (v2.uv.y - v0.uv.y) / height;

    float xstart = v0.position.x;
    float xend = v0.position.x;

    float ustart = v0.uv.x;
    float uend = v0.uv.x;
    float vstart = v0.uv.y;
    float vend = v0.uv.y;

    for (Int32 y = static_cast<Int32>(v0.position.y); y <= static_cast<Int32>(v1.position.y); ++y)
    {
      Int32 left = static_cast<Int32>(xstart);
      Int32 right = static_cast<Int32>(xend);

      // esto no debería suceder, pero si por alguna razón, left es mayor a right,
      // swapear 
      if (left > right)
        std::swap(left, right);

      float u = ustart;
      float v = vstart;
      float du = (uend - ustart) / (right - left);
      float dv = (vend - vstart) / (right - left);

      for (Int32 x = left; x <= right; ++x)
      {
        Color fcolor = pixelShader(u, v);
        ColorUInt8 colorUInt8(fcolor);
        setPixel(x, y, colorUInt8);
        u += du;
        v += dv;
      }

      xstart += dx_left;
      xend += dx_right;
      ustart += du_left;
      vstart += dv_left;
      uend += du_right;
      vend += dv_right;
    }
  }

  void Image::drawTopTriangle(
    const Triangle& triangle,
    const PixelShaderSW& pixelShader
  )
  {
    // ordenar los vértices por su coordenada x, de menor a mayor, 
    // para facilitar el rasterizado.

    Vertex v0 = triangle.v0;
    Vertex v1 = triangle.v1;
    Vertex v2 = triangle.v2;

    if (v0.position.x > v1.position.x)
      std::swap(v0, v1);

    Int32 height = static_cast<Int32>(v2.position.y - v0.position.y);
    if (height == 0) // triangulo degenerado, no se pinta 
      return;

    float dx_left = (v2.position.x - v0.position.x) / height;
    float dx_right = (v2.position.x - v1.position.x) / height;

    float du_left = (v2.uv.x - v0.uv.x) / height;
    float du_right = (v2.uv.x - v1.uv.x) / height;
    float dv_left = (v2.uv.y - v0.uv.y) / height;
    float dv_right = (v2.uv.y - v1.uv.y) / height;

    float xstart = v0.position.x;
    float xend = v1.position.x;

    float ustart = v0.uv.x;
    float uend = v1.uv.x;
    float vstart = v0.uv.y;
    float vend = v1.uv.y;

    for (Int32 y = static_cast<Int32>(v0.position.y); y <= static_cast<Int32>(v2.position.y); ++y)
    {
      Int32 left = static_cast<Int32>(xstart);
      Int32 right = static_cast<Int32>(xend);

      // esto no debería suceder, pero si por alguna razón, left es mayor a right,
      // swapear 
      if (left > right)
        std::swap(left, right);

      float u = ustart;
      float v = vstart;
      float du = (uend - ustart) / (right - left);
      float dv = (vend - vstart) / (right - left);

      for (Int32 x = left; x <= right; ++x)
      {
        /*
        float z;
        if not (z DEPTH_TEST_OP::LESS zBuffer[x, y])
          return;
        */

        Color fcolor = pixelShader(u, v);
        ColorUInt8 colorUInt8(fcolor);
        setPixel(x, y, colorUInt8);

        u += du;
        v += dv;
      }

      xstart += dx_left;
      xend += dx_right;
      ustart += du_left;
      vstart += dv_left;
      uend += du_right;
      vend += dv_right;
    }
  }
}