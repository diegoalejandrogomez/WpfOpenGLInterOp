#include "stdafx.h"
#include "SimpleTextRenderer.h"
#include "SimpleEngine.h"
#include <filesystem>
using namespace std::tr2::sys;


//Register entry as simpleID for factory
FACTORY_REGISTER(SimpleObject, SimpleTextRenderer)

SimpleTextRenderer::SimpleTextRenderer() {

	SimpleResourceManager* resources = SimpleEngine::Instance()->GetResourceManager();
	SimpleShaderProgram* p = resources->GetProgram("TextSprite");
	SetShader(p);

}
SimpleTextRenderer::~SimpleTextRenderer() {


}

void SimpleTextRenderer::Advance(float dt) {

	
	SimpleSpriteSheetRenderer::Advance(dt);

}

//The font is rendered with anchor on the lower left corner... we should add more anchor points later...
void SimpleTextRenderer::Render(float dt) {

	// Iterate through all characters
	std::string::const_iterator c;
	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	SimpleResourceManager* resources = SimpleEngine::Instance()->GetResourceManager();
	SimpleResourceManager::FontCharacters chars = resources->GetFontChars(_fontName);

	glm::vec3 pos = GetPosition();
	glm::vec3 originalPos = pos;
	float scale = resources->GetFontScale(_fontName) * _fontSize;
	SimpleSpriteSheetRenderer::SetSpriteSheet(_fontName);

	for (c = _text.begin(); c != _text.end(); c++)
	{
		SimpleResourceManager::SimpleCharacter ch = chars[*c];

		//Obtain the current position
		
		GLfloat xpos = pos.x + ch.Bearing.x * scale;
		GLfloat ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = float(ch.Size.x * scale);
		GLfloat h = float(ch.Size.y * scale);

			
		SimpleSpriteSheetRenderer::SetIndex(ch.SpriteIndex);
		SimpleSpriteSheetRenderer::SetPosition({ xpos + 0.5f*w, ypos + 0.5f* h, 0.0f });
		SimpleSpriteSheetRenderer::SetSize({ w,h });

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
	//Obtain font name
	path filePath = name;
	_fontName = filePath.filename().string();

	SimpleResourceManager* resources = SimpleEngine::Instance()->GetResourceManager();
	if (!resources->HasFont(_fontName))
		resources->LoadFont(name);
	
}

void SimpleTextRenderer::SetText(std::string text) {
	_text = text;
}

void SimpleTextRenderer::SetFontSize(float size) {

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
const float SimpleTextRenderer::GetFontSize() const {
	return _fontSize;
}

const SimpleColor& SimpleTextRenderer::GetColor() const {
	return _fontColor;
}

json SimpleTextRenderer::Serialize() {

	json so = SimpleObject::Serialize();
	json ret{
		{"text",_text},
		{"fontName", _fontName},
		{"fontSize", _fontSize},
		{"fontColor",	{_fontColor.r,
						 _fontColor.g,
						 _fontColor.b,
						 _fontColor.a
						}
		}
	};
	
	so["SimpleTextRenderer"] = ret;
	return so;

}
bool SimpleTextRenderer::Deserialize(const json &node) {

	SimpleObject::Deserialize(node);

	const json& local = node["SimpleTextRenderer"];

	SIMPLE_ASSERT(local.find("text") != local.end());
	_text = local["text"].get<std::string>();
	
	//We have already deserialized font data
	SIMPLE_ASSERT(local.find("fontName") != local.end());
	SetFontName("/fonts/" + local["fontName"].get<std::string>());
	
	SIMPLE_ASSERT(local.find("fontSize") != local.end());
	_fontSize = local["fontSize"];
	
	SIMPLE_ASSERT(local.find("fontColor") != local.end());
	SIMPLE_ASSERT(local["fontColor"].is_array());
	_fontColor.r = local["fontColor"][0];
	_fontColor.g = local["fontColor"][1];
	_fontColor.b = local["fontColor"][2];
	_fontColor.a = local["fontColor"][3];
	
	return true;
}