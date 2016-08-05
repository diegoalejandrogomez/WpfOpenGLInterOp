#include "stdafx.h"
#include "SimpleTexture.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "SimpleUtils.h"

SimpleTexture::SimpleTexture() {

	//Create texture
	glGenTextures(1, &_tex);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

	ilBindImage(0);
	ilDeleteImage(this->texture.id);
	free(this->texture.imageData);
	this->texture.width = 0;
	this->texture.height = 0;
	this->texture.id = 0;
}


void SimpleTexture::_UploadData() {
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _potSize.x, _potSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.imageData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SimpleTexture::LoadTexture(const char* path)
{

	ILuint ImgId = 0;
	IL_CHECK(ilGenImages(1, &ImgId));
	this->texture.id = ImgId;
	IL_CHECK(ilBindImage(ImgId));
	IL_CHECK(ilLoadImage(path));

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
	for (unsigned int i = 0; i < texture.height; ++i) {

		memcpy(&texture.imageData[ (texture.height-i-1) * _potSize.x * 4 ], &data[i*texture.width * 4], texture.width * 4);
			
	}
	
	_UploadData();
}

