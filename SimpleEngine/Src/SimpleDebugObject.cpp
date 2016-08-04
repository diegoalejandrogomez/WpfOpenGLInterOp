#include "stdafx.h"
#include "SimpleDebugObject.h"


SimpleDebugObject::SimpleDebugObject() {
	GLuint _vbos[2];

	GL_CHECK(glGenBuffers(2, _vbos));



}
void SimpleDebugObject::Advance(float dt) {


}

void SimpleDebugObject::Render(float dt) {
	
}


