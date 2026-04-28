#include "Texture.h"

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
		int32 intPart = static_cast<int32>(std::floor(absCoord));
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
		coord = Math::Clamp(coord, 0.0f, 1.0f);
		break;

	case TEXTURE_ADDRESS_MODE::BORDER:
		coord = Math::Clamp(coord, 0.0f, 1.0f);
		break;

	default:
		break;
	}
}


Texture::Texture(const Image& image)
{
	m_image = image;
}

void Texture::create(int32 w, int32 h, int32 bpp)
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

FColor Texture::Sample(float u, float v, SAMPLE_FILTER::E filter, TEXTURE_ADDRESS_MODE::E textureAddressMode) const
{
	AdjustTextureAddressMode(textureAddressMode, u);
	AdjustTextureAddressMode(textureAddressMode, v);

	int32 px = static_cast<int32>(u * m_image.getWidth());
	int32 py = static_cast<int32>(v * m_image.getHeight());

	px = Math::Clamp(px, 0, m_image.getWidth() - 1);
	py = Math::Clamp(py, 0, m_image.getHeight() - 1);

	FColor color(0, 0, 0);

	if (filter == SAMPLE_FILTER::POINT)
	{
		color = FColor(m_image.getPixel(px, py));
	}
	else if (filter == SAMPLE_FILTER::LINEAR)
	{
		color = linearSample(m_image, u, v);
	}
	else if (filter == SAMPLE_FILTER::ANISOTROPIC)
	{
		// TODO
		return FColor();
	}

	return color;
}

FColor Texture::linearSample(const Image& image, float u, float v) const
{
	//////// Demostración (Modo de Sampling): No hacerlo aquí
	u = Math::Clamp(u, 0.0f, 1.0f);
	v = Math::Clamp(v, 0.0f, 1.0f);
	////////

	// aquí estamos haciendo el desfase de medio pixel.
	float x = u * (image.getWidth() - 1) - 0.5f;
	float y = v * (image.getHeight() - 1) - 0.5f;

	int32 x0 = static_cast<int32>(Math::Floor(x));
	int32 y0 = static_cast<int32>(Math::Floor(y));

	int32 x1 = std::min(x0 + 1, image.getWidth() - 1);
	int32 y1 = std::min(y0 + 1, image.getHeight() - 1);
	x0 = std::max(x0, 0);
	y0 = std::max(y0, 0);

	float tx = x - x0;
	float ty = y - y0;

	FColor c00 = FColor(image.getPixel(x0, y0));
	FColor c10 = FColor(image.getPixel(x1, y0));
	FColor c01 = FColor(image.getPixel(x0, y1));
	FColor c11 = FColor(image.getPixel(x1, y1));

	FColor c0 = Lerp(c00, c10, tx);
	FColor c1 = Lerp(c01, c11, tx);

	return Lerp(c0, c1, ty);
}