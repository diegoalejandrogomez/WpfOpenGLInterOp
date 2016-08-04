#include "stdafx.h"
#include "SimpleTexture.h"

SimpleTexture::SimpleTexture() {

}

SimpleTexture::SimpleTexture(wchar_t* path) {
	this->LoadTexture(path);
	this->Render();
}

SimpleTexture::~SimpleTexture()
{
	ilBindImage(0);
	ilDeleteImage(this->texture.id);
	free(this->texture.imageData);
	this->texture.width = 0;
	this->texture.height = 0;
	this->texture.id = 0;
}

void SimpleTexture::LoadTexture(wchar_t* path)
{
	ILuint ImgId = 0;
	ilGenImages(1, &ImgId);
	this->texture.id = ImgId;
	ilBindImage(ImgId);
	ilLoadImage(path);
	this->texture.width = ilGetInteger(IL_IMAGE_WIDTH);
	this->texture.height = ilGetInteger(IL_IMAGE_HEIGHT);
	this->texture.imageData = new BYTE[this->texture.width * this->texture.height * 3];
	ilCopyPixels(0, 0, 0, texture.width, this->texture.height, 1, IL_RGB,
		IL_UNSIGNED_BYTE, this->texture.imageData);
}

void SimpleTexture::Render() {
	//Todo integrate with engine
}