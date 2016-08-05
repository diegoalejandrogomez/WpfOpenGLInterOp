#version 420
uniform sampler2D texSampler;

in vec2 texCoord;
out vec4 fragColour;
void main() {
  
  fragColour = texture(texSampler, texCoord);

    
}