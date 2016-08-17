#pragma once
#include <string>
#include "Texture.h"
#include <glm\glm.hpp>
#include <stdlib.h>

class SimpleTexture {
public:
	SimpleTexture();
	SimpleTexture(const char* path);
	~SimpleTexture();

	void LoadTexture(const char* path);
	
	int GetWidth() { return texture.width; };
	int GetHeight() { return texture.height; };

	int GetPOTWidth() { return _potSize.x; };
	int GetPOTHeight() { return _potSize.y; };

	float GetWidthRatio() { return _sizeRatio.x; };
	float GetHeightRatio() { return _sizeRatio.y; };

	void BindTo(int textureChannel);

	//No mipmaps for now...
	void SetSmooth();
	void SetPixelated();

	std::string GetPath() { return _path; }
private:
	//CPU data
	Texture texture;
	std::string _path;

	//GPU
	GLuint _tex;

	//POT size of the texture
	glm::ivec2 _potSize;
	//ratio from real size to pot size
	glm::vec2 _sizeRatio;


	void _UploadData();
};