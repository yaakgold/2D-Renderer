#pragma once
#include <string>
#include "Canvas.h"

class Image
{
public:
	Image() {}
	~Image() {}

	bool Load(const std::string& fileName, Uint8 alpha = 255);

	friend class Canvas;

private:
	std::vector<pixel_t> m_buffer;

	int m_width{ 0 }, m_height{ 0 };
};