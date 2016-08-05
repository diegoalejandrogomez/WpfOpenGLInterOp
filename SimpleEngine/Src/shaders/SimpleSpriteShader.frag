#version 420
in vec2 texCoord;
out vec4 fragColour;

uniform sampler2D texture;

void main() {
  

  fragColour = texture2D(texture, texCoord);
  
}