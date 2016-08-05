#pragma once
#include <string>
#include "Texture.h"

class SimpleTexture {
public:
	SimpleTexture();
	SimpleTexture(const char* path);
	~SimpleTexture();

	void LoadTexture(const char* path);
	
	int GetWidth() { return texture.width; };
	int GetHeight() { return texture.height; };

	void BindTo(int textureChannel);
private:
	//CPU data
	Texture texture;

	//GPU
	GLuint _tex;


	void _UploadData();
};