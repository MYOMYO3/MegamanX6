#pragma once
#include "Render.h"

class Image;
class ImageRender : public JRender
{
private:
	Image* image;

public:
	void Image(const wchar_t* _Name);
	void Render() override;
public:
	ImageRender();
	~ImageRender();
};

