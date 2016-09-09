#pragma once
#include "SimpleConfiguration.h"
#include <unordered_map>
#include "SimpleShaderProgram.h"
#include "SimpleID.h"
#include "SimpleTexture.h"
#include "SimpleSpriteSheet.h"
#include "SimpleSpriteAnimation.h"

class SIMPLE_API SimpleResourceManager {
public:

	//Font library
	struct SimpleCharacter {
		uint32_t SpriteIndex;
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		long  Advance;    // Offset to advance to next glyph
	};
	using FontCharacters = std::vector<SimpleCharacter>;

	
	
	void SetResourcesBaseDir(std::string const& baseDir) { _resBaseDir = baseDir; }
	std::string GetResourcesBaseDir() { return _resBaseDir; };

	
	bool CreateProgram(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
	SimpleShaderProgram* GetProgram(SimpleID name) const;

	bool LoadTexture(std::string texturePath);
	SimpleTexture* GetTexture(SimpleID name);

	bool CreateSpriteSheet(std::string texturePath, glm::ivec2 frameSize, glm::ivec2 frameCount);
	bool CreateSpriteSheet(std::string texturePath);
	SimpleSpriteSheet* GetSpriteSheet(SimpleID texturePath);

	bool CreateSpriteAnimation(std::string name, std::string spriteSheet, std::vector<int> &frames, float frameTime);
	bool CreateSpriteAnimation(std::string name);

	SimpleSpriteAnimation* GetSpriteAnimation(SimpleID name);

	//Fonts
	bool LoadFont(std::string fontPath, uint32_t size = 48);
	bool HasFont(SimpleID fontName);
	FontCharacters GetFontChars(SimpleID fontName);
	float GetFontScale(SimpleID fontName);

	void ClearResources();
	bool SerializeResources(std::string dir);
	bool DeserializeResources(std::string dir);
	bool DeserializeResources(std::string dir, std::string subPath);

	void ExportResources(std::string exportPath);
	
	void ImportResources(std::string exportPath);
	void ImportResources(std::string exportPath, std::string subPath);

private:
	void _AddFilesToArchive(std::vector<std::string>& files, std::string relativePath, std::string archiveName);

	std::string _resBaseDir;
	//This class also serves as a mini graphics resource admin
	//Memory owners
	std::unordered_map<SimpleID, SimpleShaderProgram*> _programs;
	std::unordered_map<SimpleID, SimpleTexture*> _textures;
	std::unordered_map<SimpleID, SimpleSpriteSheet*> _spriteSheets;
	//Don't own anything
	std::unordered_map<SimpleID, SimpleSpriteAnimation*> _spriteAnimations;
	std::unordered_map<SimpleID, std::pair<float, FontCharacters>> _fonts;


};

