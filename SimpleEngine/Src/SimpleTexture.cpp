#include "stdafx.h"
#include "SimpleTexture.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "SimpleUtils.h"
#include "SimpleEngine.h"
#include "SimpleTextureRegion.h"

SimpleTexture::SimpleTexture() {

	//Create texture
	glGenTextures(1, &_tex);
	SetSmooth();
}


void SimpleTexture::SetSmooth() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

}
void SimpleTexture::SetPixelated() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

SimpleTexture::SimpleTexture(const char* path) {
	this->LoadTexture(path);
}

void SimpleTexture::BindTo(int textureChannel) {

	glActiveTexture(GL_TEXTURE0 + textureChannel);
	glBindTexture(GL_TEXTURE_2D, _tex);
}

SimpleTexture::~SimpleTexture()
{
	glDeleteTextures(1, &_tex);
	delete[] texture.imageData;
	this->texture.width = 0;
	this->texture.height = 0;
	this->texture.id = 0;
}


void SimpleTexture::_UploadData() {
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex);
	glTexImage2D(GL_TEXTURE_2D, 0, texture.internalFormat, _potSize.x, _potSize.y, 0, texture.dataFormat, texture.dataType, texture.imageData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SimpleTexture::LoadTexture(const char* path, bool autoFlush)
{

	std::string resPath = SimpleEngine::Instance()->GetResourceManager()->GetResourcesBaseDir() + path;
	ILuint ImgId = 0;
	IL_CHECK(ilGenImages(1, &ImgId));
	this->texture.id = ImgId;
	IL_CHECK(ilBindImage(ImgId));
	IL_CHECK(ilLoadImage(resPath.c_str()));

	this->texture.width = ilGetInteger(IL_IMAGE_WIDTH);
	this->texture.height = ilGetInteger(IL_IMAGE_HEIGHT);
	
	//create as pot texture
	_potSize.x = SimpleUtils::NextPOT(texture.width);
	_potSize.y = SimpleUtils::NextPOT(texture.height);
	
	_sizeRatio.x = texture.width / (float)_potSize.x;
	_sizeRatio.y = texture.height / (float)_potSize.y;

	ILenum format = ilGetInteger(IL_IMAGE_FORMAT);
	ILenum type = ilGetInteger(IL_IMAGE_TYPE);
	
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	
	ILubyte *data = ilGetData();
	texture.imageData = new BYTE[_potSize.x * _potSize.y * 4];
	memset(texture.imageData, 0, _potSize.x * _potSize.y * 4);
	for (unsigned int i = 0; i < texture.height ; ++i) {

		memcpy(&texture.imageData[ (texture.height-i-1) * _potSize.x * 4 ], &data[i*texture.width * 4], texture.width * 4);
			
	}
	
	texture.dataFormat = GL_RGBA;
	texture.internalFormat = GL_RGBA;
	texture.dataType = GL_UNSIGNED_BYTE;
	if(autoFlush)
		_UploadData();

	_path = path;

	ilBindImage(0);
	ilDeleteImage(this->texture.id);

}


void SimpleTexture::LoadTextureFromMemory(const uint8_t* data, uint8_t channels, uint32_t width, uint32_t height, bool autoFlush)
{

	this->texture.id = 0;
	
	this->texture.width = width;
	this->texture.height = height;

	texture.channels = channels;

	//create as pot texture
	_potSize.x = SimpleUtils::NextPOT(texture.width);
	_potSize.y = SimpleUtils::NextPOT(texture.height);

	_sizeRatio.x = texture.width / (float)_potSize.x;
	_sizeRatio.y = texture.height / (float)_potSize.y;

	texture.imageData = new uint8_t[_potSize.x * _potSize.y * channels];
	memset(texture.imageData, 0, _potSize.x * _potSize.y * channels);

	if(data != nullptr)
		for (uint32_t i = 0; i < texture.height; ++i)
			memcpy( &texture.imageData[(texture.height - i - 1) * _potSize.x * channels], &data[i*texture.width * channels], texture.width * channels);
	

	switch (channels)
	{
	case 1:
		texture.dataFormat = GL_RED;
		texture.internalFormat = GL_RED;
		break;
	case 4:
		texture.dataFormat = GL_RGBA;
		texture.internalFormat = GL_RGBA;
		break;
	default:
		break;
	}
	texture.dataType = GL_UNSIGNED_BYTE;
	if(autoFlush)
		_UploadData();

	_path = "MEMORY";
}



uint8_t* SimpleTexture::Pixel(uint32_t x, uint32_t y){
	uint32_t pos = y * _potSize.x * texture.channels + x * texture.channels;
	SIMPLE_ASSERT(pos < _potSize.x * _potSize.y * texture.channels);
	return &texture.imageData[pos];
}

void SimpleTexture::SetSubTexture(SimpleTextureRegion region, SimpleTexture* tex) {

	//Check sizes (we could check also for boundaries... but not for now)
	SIMPLE_ASSERT(region.Width() == tex->GetWidth() && region.Height() == tex->GetHeight());
	
	//When size is not POT, center is biased to the right

	for (int i = 0;i < (int32_t)region.Height() ; ++i) {
		for (int j = 0;j < (int32_t)region.Width() ; ++j) {
			uint8_t* pixel = Pixel(region.lowerLeft.x + j , region.lowerLeft.y + i);
			const uint8_t* other = tex->Pixel(j, i);
			for(int k = 0; k < (int32_t)texture.channels; ++k)
				pixel[k] = other[k];
			
			
		}
	}



}

void SimpleTexture::SaveTexture(const char* path) {

	ILuint ImgId = 0;
	IL_CHECK(ilGenImages(1, &ImgId));
	this->texture.id = ImgId;
	IL_CHECK(ilBindImage(ImgId));
	uint32_t format = texture.channels == 1 ? IL_LUMINANCE : IL_RGBA;
	IL_CHECK(ilTexImage(texture.width, texture.height, 1, texture.channels, format, IL_UNSIGNED_BYTE, texture.imageData));
	ilEnable(IL_FILE_OVERWRITE);
	std::string finalPath = SimpleEngine::Instance()->GetResourceManager()->GetResourcesBaseDir() + path;
	ilSave(IL_PNG, finalPath.c_str() );

}