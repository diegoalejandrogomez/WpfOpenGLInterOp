#pragma once
#include <string>
#include "Texture.h"
#include <glm\glm.hpp>
#include <stdlib.h>
#include "SimpleConfiguration.h"

class SIMPLE_API SimpleTexture {
public:
	SimpleTexture();
	SimpleTexture(const char* path);
	~SimpleTexture();

	void LoadTexture(const char* path);
	void LoadTextureFromMemory(const uint8_t* data, uint8_t channels, uint8_t width, uint8_t height);
	
	int GetWidth()const { return texture.width; };
	int GetHeight()const { return texture.height; };

	int GetPOTWidth()const { return _potSize.x; };
	int GetPOTHeight()const { return _potSize.y; };

	float GetWidthRatio()const { return _sizeRatio.x; };
	float GetHeightRatio()const { return _sizeRatio.y; };

	void BindTo(int textureChannel);

	//No mipmaps for now...
	void SetSmooth();
	void SetPixelated();

	GLuint GetNativeTexture() { return _tex; };

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