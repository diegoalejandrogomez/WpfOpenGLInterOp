#pragma once
#include "stdafx.h"
#include <GL/glew.h>
typedef struct
{
	GLubyte* imageData;         // Hold All The Color Values For The Image.     
	GLuint width;               // The Width Of The Entire Image.  
	GLuint height;              // The Height Of The Entire Image. 
	GLuint id;               // Texture ID For Use With glBindTexture.  
	uint32_t channels;
	GLenum internalFormat;
	GLenum dataFormat;
	GLenum dataType;
} Texture;