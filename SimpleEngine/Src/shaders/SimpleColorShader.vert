#version 420
in vec2 position;
in vec3 vcolour;
out vec3 fcolour;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

void main(){

	gl_Position = viewProjectionMatrix * modelMatrix* vec4(position.x, position.y, 0.0, 1.0);
	fcolour = vcolour;
	
}



