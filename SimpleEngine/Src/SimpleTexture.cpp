#include "stdafx.h"
#include "SimpleTexture.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "SimpleUtils.h"

SimpleTexture::SimpleTexture() {

	//Create texture
	glGenTextures(1, &_tex);
}

SimpleTexture::SimpleTexture(const char* path) {
	this->LoadTexture(path);
}

void SimpleTexture::BindTo(int textureChannel) {
	glActiveTexture(GL_TEXTURE0 + textureChannel);
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.imageData);
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
	
	_sizeRatio.x = _potSize.x / (float)texture.width;
	_sizeRatio.y = _potSize.y / (float)texture.height;

	ILenum format = ilGetInteger(IL_IMAGE_FORMAT);
	ILenum type = ilGetInteger(IL_IMAGE_TYPE);
	
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	
	this->texture.imageData = new BYTE[this->texture.width * this->texture.height * 4];
	IL_CHECK(ilCopyPixels(0, 0, 0, texture.width, this->texture.height, 1, IL_RGBA,
		IL_UNSIGNED_BYTE, this->texture.imageData));
	
	_UploadData();
}

