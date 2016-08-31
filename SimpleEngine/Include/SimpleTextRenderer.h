#pragma once
#include "SimpleConfiguration.h"
#include "SimpleObject.h"
#include "SimpleSpriteRenderer.h"
#include "SimpleColor.h"

class SIMPLE_API SimpleTextRenderer : public SimpleSpriteRenderer {
public:

	SimpleTextRenderer();
	~SimpleTextRenderer();

	virtual void Advance(float dt);
	virtual void Render(float dt);

	void SetText(std::string text);
	void SetFontName(std::string && name);
	void SetFontSize(uint32_t size);
	void SetColor(SimpleColor color);
	
	const std::string& GetText() const;
	const std::string &GetFontName() const;
	const uint32_t GetFontSize() const;
	const SimpleColor &GetColor() const;

	virtual SimpleID GetType() { return "SimpleTextRenderer"; }

	virtual json Serialize();
	virtual bool Deserialize(const json &node);

private:

	std::string _text;
	std::string _fontName;
	uint32_t _fontSize;
	SimpleColor _fontColor;

};