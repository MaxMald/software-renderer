#include "ge/graphics/geTexture.h"

namespace ge
{
  void AdjustTextureAddressMode(TEXTURE_ADDRESS_MODE::E mode, float& coord)
  {
    switch (mode)
    {
    case TEXTURE_ADDRESS_MODE::WRAP:
      coord = std::fmod(coord, 1.0f);
      if (coord < 0)
        coord += 1.0f;
      break;

    case TEXTURE_ADDRESS_MODE::MIRROR:
    {
      float absCoord = std::abs(coord);
      Int32 intPart = static_cast<Int32>(std::floor(absCoord));
      float fracPart = absCoord - intPart;
      if (intPart % 2 == 0)
        coord = fracPart;
      else
        coord = 1.0f - fracPart;
    }
    if (coord < 0)
      coord += 1.0f;
    break;

    case TEXTURE_ADDRESS_MODE::CLAMP:
      coord = hc::Math::Clamp(coord, 0.0f, 1.0f);
      break;

    case TEXTURE_ADDRESS_MODE::BORDER:
      coord = hc::Math::Clamp(coord, 0.0f, 1.0f);
      break;

    default:
      break;
    }
  }


  Texture::Texture(const Image& image)
  {
    m_image = image;
  }

  void Texture::create(Int32 w, Int32 h, Int32 bpp)
  {
    m_image.create(w, h, bpp);
  }

  void Texture::create(const Image& image)
  {
    m_image = image;
  }

  void Texture::unload()
  {
    m_image.unload();
  }


  void Texture::GenerateMipmap()
  {
    // TODO
  }

  Color Texture::Sample(float u, float v, SAMPLE_FILTER::E filter, TEXTURE_ADDRESS_MODE::E textureAddressMode) const
  {
    AdjustTextureAddressMode(textureAddressMode, u);
    AdjustTextureAddressMode(textureAddressMode, v);

    Int32 px = static_cast<Int32>(u * m_image.getWidth());
    Int32 py = static_cast<Int32>(v * m_image.getHeight());

    px = hc::Math::Clamp(px, 0, m_image.getWidth() - 1);
    py = hc::Math::Clamp(py, 0, m_image.getHeight() - 1);

    Color color(0, 0, 0);

    if (filter == SAMPLE_FILTER::POINT)
    {
      color = m_image.getPixel(px, py).toColor();
    }
    else if (filter == SAMPLE_FILTER::LINEAR)
    {
      color = linearSample(m_image, u, v);
    }
    else if (filter == SAMPLE_FILTER::ANISOTROPIC)
    {
      // TODO
      return Color();
    }

    return color;
  }

  Color Texture::linearSample(const Image& image, float u, float v) const
  {
    //////// Demostración (Modo de Sampling): No hacerlo aquí
    u = hc::Math::Clamp(u, 0.0f, 1.0f);
    v = hc::Math::Clamp(v, 0.0f, 1.0f);
    ////////

    // aquí estamos haciendo el desfase de medio pixel.
    float x = u * (image.getWidth() - 1) - 0.5f;
    float y = v * (image.getHeight() - 1) - 0.5f;

    Int32 x0 = static_cast<Int32>(hc::Math::Floor(x));
    Int32 y0 = static_cast<Int32>(hc::Math::Floor(y));

    Int32 x1 = std::min(x0 + 1, image.getWidth() - 1);
    Int32 y1 = std::min(y0 + 1, image.getHeight() - 1);
    x0 = std::max(x0, 0);
    y0 = std::max(y0, 0);

    float tx = x - x0;
    float ty = y - y0;

    Color c00 = image.getPixel(x0, y0).toColor();
    Color c10 = image.getPixel(x1, y0).toColor();
    Color c01 = image.getPixel(x0, y1).toColor();
    Color c11 = image.getPixel(x1, y1).toColor();

    Color c0 = Color::Lerp(c00, c10, tx);
    Color c1 = Color::Lerp(c01, c11, tx);

    return Color::Lerp(c0, c1, ty);
  }
}