#include "stdafx.h"
#include "SimpleTextRenderer.h"
#include "SimpleEngine.h"

SimpleTextRenderer::SimpleTextRenderer() {

	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	SimpleShaderProgram* p = render->GetProgram("TextSprite");
	SetShader(p);

}
SimpleTextRenderer::~SimpleTextRenderer() {


}

void SimpleTextRenderer::Advance(float dt) {

	
	SimpleSpriteRenderer::Advance(dt);

}

//The font is rendered with anchor on the lower left corner... we should add more anchor points later...
void SimpleTextRenderer::Render(float dt) {

	// Iterate through all characters
	std::string::const_iterator c;
	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	SimpleRenderer::FontCharacters chars = render->GetFontChars(_fontName);

	glm::vec3 pos = GetPosition();
	glm::vec3 originalPos = pos;
	float scale = render->GetFontScale(_fontName) * _fontSize;

	for (c = _text.begin(); c != _text.end(); c++)
	{
		SimpleRenderer::SimpleCharacter ch = chars[*c];

		//Obtain the current position
		
		GLfloat xpos = pos.x + ch.Bearing.x * scale;
		GLfloat ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = float(ch.Size.x * scale);
		GLfloat h = float(ch.Size.y * scale);

			
		SimpleSpriteRenderer::SetAsTexture(ch.Texture);
		SimpleSpriteRenderer::SetPosition({ xpos + 0.5f*w, ypos + 0.5f* h, 0.0f });
		SimpleSpriteRenderer::SetSize({ w,h });

		_shader->Bind();
		GLuint textColor = _shader->GetLocationFor("textColor");
		glUniform4f(textColor, _fontColor.r / 255.0f, _fontColor.g / 255.0f, _fontColor.b / 255.0f, _fontColor.a / 255.0f);
		SimpleSpriteRenderer::Render(0.0f);

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		 pos.x+= (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	
	SetPosition(originalPos);
	
}

void SimpleTextRenderer::SetFontName(std::string && name) {
	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	if (!render->HasFont(name)) {
		if (render->LoadFont(name))
			_fontName = name;
	}
	else {
		_fontName = name;

	}	
}

void SimpleTextRenderer::SetText(std::string text) {
	_text = text;
}

void SimpleTextRenderer::SetFontSize(uint32_t size) {

	_fontSize = size;

}
void SimpleTextRenderer::SetColor(SimpleColor color) {
	_fontColor = color;
}

const std::string& SimpleTextRenderer::GetText() const {
	return _text;
}
const std::string& SimpleTextRenderer::GetFontName() const{
	return _fontName;
}
const uint32_t SimpleTextRenderer::GetFontSize() const {
	return _fontSize;
}

const SimpleColor& SimpleTextRenderer::GetColor() const {
	return _fontColor;
}

json SimpleTextRenderer::Serialize() {

	json obj = json::object;
	return obj;

}
bool SimpleTextRenderer::Deserialize(const json &node) {


	return true;
}