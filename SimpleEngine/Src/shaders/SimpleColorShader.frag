#version 420
in vec3 fcolour;
out vec4 fragColour;

void main() {
  fragColour = vec4(fcolour.r,fcolour.g,fcolour.b, 1.0);
  //fragColour = vec4(0.0,1.0,0.0, 1.0);
}