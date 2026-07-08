#pragma once

#include "Commons.h"
#include "Color.h"
#include "FColor.h"
#include "Triangle.h"

class Image
{
public:
	Image();
	~Image() = default;

	void create(int32 w, int32 h, int32 bpp);
	void load(const char* filename);
	void unload();
	void clear(const Color& color);
	void setPixel(int32 x, int32 y, const Color& color);
	Color getPixel(int32 x, int32 y) const;
	int32 computeRegionCode(int32 x, int32 y, int32 xMin, int32 yMin, int32 xMax, int32 yMax) const;

	/**
	 * Clips a line defined by the endpoints (x0, y0) and (x1, y1) 
	 * against the boundaries of the image. The function modifies the endpoints of the 
	 * line to fit within the image boundaries.
	 */
	bool clipLine(int32& x0, int32& y0, int32& x1, int32& y1) const;
	void line(int32 x0, int32 y0, int32 x1, int32 y1, const Color& color);
	void bressenhamLine(int32 x0, int32 y0, int32 x1, int32 y1, const Color& color);
	void bressehamCircle(int32 centerX, int32 centerY, int32 radius, const Color& color);
	void bitBlt(int32 x, int32 y, const Image& src);
	void drawTriangle(
		int32 x0,
		int32 y0,
		int32 x1,
		int32 y1,
		int32 x2,
		int32 y2,
		const Color& color
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
	int32 getWidth() const { return m_width; }
	int32 getHeight() const { return m_height; }
	int32 getBPP() const { return m_bpp; }
	int32 getPitch() const { return m_width * getBytesPerPixel(); }
	int32 getBytesPerPixel() const { return m_bpp >> 3; } // >> 3 is the same as / 8
	byte* getData() { return m_data.data(); }

private:
	int32 m_width;
	int32 m_height;
	int32 m_bpp;
	Vector<byte> m_data;
};