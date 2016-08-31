#version 420
in vec2 position;
in vec2 uv;

out vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;
uniform vec2 uvOffset;
uniform vec2 uvSize;
//To compensate on non POT textures
uniform vec2 sizeRatio;

void main(){

	gl_Position = viewProjectionMatrix * modelMatrix* vec4(position.x, position.y, 0.0, 1.0);
	texCoord = (uv * uvSize + uvOffset) * sizeRatio;
	
}



