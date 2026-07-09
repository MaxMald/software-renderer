#pragma once

#include "geCorePrerequisites.h"
#include "geImage.h"

namespace ge
{
  class GE_CORE_EXPORT Texture
  {
  public:
    Texture() = default;
    explicit Texture(const Image& image);
    ~Texture() = default;

    void create(Int32 w, Int32 h, Int32 bpp);
    void create(const Image& image);
    void unload();
    Color Sample(
      float u, float v,
      SAMPLE_FILTER::E filter,
      TEXTURE_ADDRESS_MODE::E textureAddressMode = TEXTURE_ADDRESS_MODE::WRAP
    ) const;
    void GenerateMipmap();

    inline Image& getImage() { return m_image; }

  private:
    Image m_image;

    Color linearSample(const Image& image, float x, float y) const;
  };
}

