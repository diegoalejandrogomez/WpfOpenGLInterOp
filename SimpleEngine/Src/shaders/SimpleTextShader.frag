#version 420
uniform sampler2D texSampler;
uniform vec4 textColor;
in vec2 texCoord;
out vec4 fragColour;
void main() {
  
  vec4 color = texture(texSampler, texCoord);
  color.gba = color.rrr;
  color *= textColor;
  fragColour = color;

    
}