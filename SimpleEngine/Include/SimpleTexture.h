#pragma once
#include <string>
#include "Texture.h"
#include <glm\glm.hpp>
#include <stdlib.h>
#include "SimpleConfiguration.h"
#include "SimpleAABB.h"
#include "SimpleTextureRegion.h"

class SIMPLE_API SimpleTexture {
public:
	SimpleTexture();
	SimpleTexture(const char* path);
	~SimpleTexture();

	void LoadTexture(const char* path, bool autoFlush=true);
	void LoadTextureFromMemory(const uint8_t* data, uint8_t channels, uint32_t width, uint32_t height, bool autoFlush= true);
	void SaveTexture(const char* path);

	void SetSubTexture(SimpleTextureRegion  region, SimpleTexture* tex);

	int GetWidth()const { return texture.width; };
	int GetHeight()const { return texture.height; };

	int GetPOTWidth()const { return _potSize.x; };
	int GetPOTHeight()const { return _potSize.y; };

	float GetWidthRatio()const { return _sizeRatio.x; };
	float GetHeightRatio()const { return _sizeRatio.y; };

	void BindTo(int textureChannel);
	void Flush() { _UploadData(); }
	

	uint8_t* Pixel(uint32_t x, uint32_t y);

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