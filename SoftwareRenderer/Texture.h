#pragma once

#include "Commons.h"
#include "Image.h"

class Texture
{
public:
	Texture() = default;	
	explicit Texture(const Image& image);
	~Texture() = default;

	void create(int32 w, int32 h, int32 bpp);
	void create(const Image& image);
	void unload();
	FColor Sample(float u, float v, SAMPLE_FILTER::E filter, TEXTURE_ADDRESS_MODE::E textureAddressMode = TEXTURE_ADDRESS_MODE::WRAP) const;
	void GenerateMipmap();

	inline Image& getImage() { return m_image; }

private:
	Image m_image;

	FColor linearSample(const Image& image, float x, float y) const;
};