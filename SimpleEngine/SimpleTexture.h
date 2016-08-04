#pragma once
#include <string>
#include "Texture.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

class SimpleTexture {
public:
	SimpleTexture();
	SimpleTexture(wchar_t* path);
	~SimpleTexture();

	void LoadTexture(wchar_t* path);
	void Render();
private:
	Texture texture;
};