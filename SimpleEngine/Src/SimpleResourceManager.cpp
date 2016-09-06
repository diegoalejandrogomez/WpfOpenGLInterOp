#include "stdafx.h"
#include "SimpleResourceManager.h"
#include <filesystem>
#include "SimpleUtils.h"
#include <iostream>
#include <fstream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "SimpleEngine.h"
#include <zip.h>

//C++ 14/17 ... but why not XD
using namespace std::tr2::sys;

void SimpleResourceManager::ClearResources() {

	for (auto &shader : _programs)
		delete shader.second;
	_programs.clear();

	for (auto &tex : _textures)
		delete tex.second;
	_textures.clear();

	for (auto &sheet : _spriteSheets)
		delete sheet.second;
	_spriteSheets.clear();

	for (auto &animation : _spriteAnimations)
		delete animation.second;
	_spriteAnimations.clear();

}


bool SimpleResourceManager::CreateProgram(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {

	//Don't reload if it already exists
	if (_programs.find(name) == _programs.end()) {
		SimpleShaderProgram* program = new SimpleShaderProgram();
		if (!program->CompileFromFile(vertexShaderPath, fragmentShaderPath)) {
			SIMPLE_LOG("Coulnd't compile shader %s", name);
			return false;
		}
		if (!program->Link()) {
			SIMPLE_LOG("Coulnd't link shader %s", name);
			return false;
		}
		_programs[name] = program;
	}

	return true;
}

SimpleShaderProgram* SimpleResourceManager::GetProgram(SimpleID name) const {
	auto it = _programs.find(name);
	if (it == _programs.end())
		return nullptr;
	return it->second;
}


bool SimpleResourceManager::LoadTexture(std::string texturePath) {

	if (_textures.find(texturePath) != _textures.end())
		return true; //Already loaded
	SimpleTexture* _tex = new SimpleTexture();
	_tex->LoadTexture(texturePath.c_str());
	_textures[texturePath] = _tex;
	return true;
}

SimpleTexture* SimpleResourceManager::GetTexture(SimpleID texturePath) {
	auto tex = _textures.find(texturePath);
	if (tex == _textures.end())
		return nullptr;
	return tex->second;
}

//Equally spaced sprite sheet. Automatically creates the frames
bool SimpleResourceManager::CreateSpriteSheet(std::string texturePath, glm::ivec2 frameSize, glm::ivec2 frameCount) {

	auto sheet = _spriteSheets.find(texturePath);
	if (sheet == _spriteSheets.end()) {
		//Try to load the texture
		SimpleSpriteSheet* spriteSheet = new SimpleSpriteSheet();
		spriteSheet->LoadTexture(texturePath.c_str());
		spriteSheet->CreateUniformFrames(frameSize, frameCount);
		_spriteSheets[texturePath] = spriteSheet;

	}

	return true;
}

//Arbitrary sprite sheet. Must call AddSpriteFrame to set them
bool SimpleResourceManager::CreateSpriteSheet(std::string texturePath) {

	auto sheet = _spriteSheets.find(texturePath);
	if (sheet == _spriteSheets.end()) {
		//Try to load the texture	
		SimpleSpriteSheet* spriteSheet = new SimpleSpriteSheet();
		spriteSheet->LoadTexture(texturePath.c_str());
		_spriteSheets[texturePath] = spriteSheet;
	}

	return true;
}

SimpleSpriteSheet* SimpleResourceManager::GetSpriteSheet(SimpleID texturePath) {
	auto sheet = _spriteSheets.find(texturePath);
	if (sheet == _spriteSheets.end())
		return nullptr;
	return sheet->second;

}

bool SimpleResourceManager::CreateSpriteAnimation(std::string name, std::string spriteSheet, std::vector<int> &frames, float frameTime) {

	//Check if it doesn't exist already

	if (_spriteAnimations.find(name) == _spriteAnimations.end()) {
		SimpleSpriteAnimation* anim = new SimpleSpriteAnimation();
		anim->SetAnimationName(name);
		anim->SetSpriteSheet(spriteSheet);
		anim->SetFrames(frames);
		anim->SetFrameTime(frameTime);
		_spriteAnimations[name] = anim;
		return true;
	}

	return true;

}

bool SimpleResourceManager::CreateSpriteAnimation(std::string name) {

	//Check if it doesn't exist already

	if (_spriteAnimations.find(name) == _spriteAnimations.end()) {
		SimpleSpriteAnimation* anim = new SimpleSpriteAnimation();
		anim->SetAnimationName(name);
		_spriteAnimations[name] = anim;
		return true;
	}
	return true;

}


SimpleSpriteAnimation* SimpleResourceManager::GetSpriteAnimation(SimpleID name) {
	auto it = _spriteAnimations.find(name);

	if (it == _spriteAnimations.end())
		return nullptr;

	return it->second;
}





//Serializes the currently loaded resources
bool SimpleResourceManager::SerializeResources(std::string dir) {

	//Programs and textures aren't serialized
	json spriteSheets = json::array();
	path p = dir + +"/spriteSheets/";
	remove_all(p);
	create_directory(p);

	for (auto &sheet : _spriteSheets) {

		if (!sheet.second->IsSerializable())
			continue;

		std::string  filename = sheet.second->GetPath();
		std::replace(filename.begin(), filename.end(), '/', '_');
		filename = p.generic_string() + filename + ".sheet";

		std::ofstream out(filename);

		if (!out.is_open()) {
			SIMPLE_LOG("Couldn't serialize spritesheets");
			return false;
		}
		json sprSheet = sheet.second->Serialize();
		out << std::setw(4) << sprSheet;
		out.close();
	}

	p = dir + "/animations/";
	remove_all(p);
	create_directory(p);

	for (auto &anim : _spriteAnimations) {

		if (!anim.second->IsSerializable())
			continue;

		std::string  filename = anim.second->GetAnimationName();
		std::replace(filename.begin(), filename.end(), '/', '_');
		filename = p.generic_string() + filename + ".anim";

		std::ofstream out(filename);

		if (!out.is_open()) {
			SIMPLE_LOG("Couldn't serialize animations");
			return false;
		}
		json sprAnim = anim.second->Serialize();
		out << std::setw(4) << sprAnim;
		out.close();
	}

	return true;
}



bool SimpleResourceManager::DeserializeResources(std::string dir) {

	//Load spriteSheets
	path p = dir + "/spriteSheets/";
	for (const auto& entry : directory_iterator{ p })
	{
		if (is_regular_file(entry.status()))
		{
			std::ifstream in(entry.path().generic_string());
			if (!in.is_open())
				return false;

			json sprSheet;
			in >> sprSheet;
			SimpleSpriteSheet* sheet = new SimpleSpriteSheet();
			sheet->Deserialize(sprSheet);
			_spriteSheets[sheet->GetPath()] = sheet;
			in.close();
		}
		else if (is_directory(entry.status()))
		{
			SIMPLE_LOG("Skipping directory %s", entry.path());
		}
	}


	p = dir + "/animations/";

	for (const auto& entry : directory_iterator{ p })
	{
		if (is_regular_file(entry.status()))
		{
			std::ifstream in(entry.path().generic_string());
			if (!in.is_open())
				return false;

			json sprAnim;
			in >> sprAnim;
			SimpleSpriteAnimation* anim = new SimpleSpriteAnimation();
			anim->Deserialize(sprAnim);
			_spriteAnimations[anim->GetAnimationName()] = anim;
			in.close();
		}
		else if (is_directory(entry.status()))
		{
			SIMPLE_LOG("Skipping directory %s", entry.path());
		}
	}

	return true;
}


void SimpleResourceManager::_AddFilesToArchive(std::vector<std::string>& files, std::string relativePath, std::string archiveName) {

	
	zip_source_t *src;
	zip_error_t error;
		
	zip_error_init(&error);
	int ierror;
	zip *zipArchive = zip_open(archiveName.c_str(), ZIP_CREATE, &ierror);
	if (zipArchive == NULL) {
		
		SIMPLE_LOG("%s", zip_error_strerror(&error));
		zip_error_fini(&error);
		return;
	}
	if(!relativePath.empty())
		zip_dir_add(zipArchive, relativePath.c_str(), ZIP_FL_OVERWRITE);

	std::string base = SimpleEngine::Instance()->GetResourceManager()->GetResourcesBaseDir();
	for (auto file : files) {

		std::string entryPath = relativePath.empty()? file : relativePath  + "/" + file;
		std::string finalPath = base +  entryPath;

		src = zip_source_file_create(finalPath.c_str(),0,0, &error);

		if (src == NULL) {
			SIMPLE_LOG("%s", zip_error_strerror(&error));
			zip_error_fini(&error);
			zip_close(zipArchive);
			return;

		}

		int index = (int)zip_file_add(zipArchive, entryPath.c_str(), src, ZIP_FL_OVERWRITE);
		if (index < 0)
		{
			SIMPLE_LOG("Couldn't add file to archive");
			return;
		}

	}
		
	zip_close(zipArchive);
}
void SimpleResourceManager::ExportResources(std::string exportPath) {
		
	std::string base = SimpleEngine::Instance()->GetResourceManager()->GetResourcesBaseDir();

	SerializeResources(base);

	if (exists(exportPath))
		remove(exportPath);

	//Font packing
	std::vector<std::string> files;
	SimpleUtils::GetFolderContents(base + "/fonts/", files);
	_AddFilesToArchive(files, "fonts", exportPath);

	//Texture packing
	files.clear();
	SimpleUtils::GetFolderContents(base + "/media/", files);
	_AddFilesToArchive(files, "media", exportPath);

	//Animations packing
	files.clear();
	SimpleUtils::GetFolderContents(base + "/animations/", files);
	_AddFilesToArchive(files, "animations", exportPath);

	//Spritesheets packing
	files.clear();
	SimpleUtils::GetFolderContents(base + "/spriteSheets/", files);
	_AddFilesToArchive(files, "spriteSheets", exportPath);

	files.clear();
	SimpleUtils::GetFolderContents(base + "/", files);
	_AddFilesToArchive(files, "", exportPath);

}

void SimpleResourceManager::ImportResources(std::string exportPath) {
	std::string base = SimpleEngine::Instance()->GetResourceManager()->GetResourcesBaseDir();

	
	//if (exists(base + "fonts"))
	//	remove(base + "fonts");
	//if (exists(base + "media"))
	//	remove(base + "media");
	//if (exists(base + "animations"))
	//	remove(base + "animations");
	//if (exists(base + "spriteSheets"))
	//	remove(base + "spriteSheets");

	//Create directory structure
	create_directory(base + "fonts");
	create_directory(base + "media");
	create_directory(base + "animations");
	create_directory(base + "spriteSheets");

	zip_source_t *src;
	zip_error_t error;

	zip_error_init(&error);
	int ierror;
	zip *zipArchive = zip_open(exportPath.c_str(), ZIP_RDONLY, &ierror);
	if (zipArchive == NULL) {

		SIMPLE_LOG("%s", zip_error_strerror(&error));
		zip_error_fini(&error);
		return;
	}
	
	uint32_t fileCount = zip_get_num_entries(zipArchive, 0);
	char buffer[100];

	for (uint32_t i = 0; i < fileCount; ++i) {
		zip_stat_t stat;
		zip_stat_index(zipArchive, i, 0, &stat);
		
		if (stat.size == 0)
			continue;
		std::ofstream out(base + stat.name , std::ios::binary | std::ios::trunc);
		
		zip_file_t *zipFile = zip_fopen_index(zipArchive, i, 0);
		uint8_t readBytes = zip_fread(zipFile, buffer, 100);
		while (readBytes > 0) {
			out.write(buffer, readBytes);
			readBytes = zip_fread(zipFile, buffer, 100);
		}
	
		zip_fclose(zipFile);
		out.close();
	}

	zip_discard(zipArchive);
	zip_close(zipArchive);
	DeserializeResources(base);
}


bool SimpleResourceManager::LoadFont(std::string fontPath, uint32_t size) {
	//Font management
	FT_Library _fontLib;
	if (FT_Init_FreeType(&_fontLib))
		SIMPLE_LOG("FREETYPE: Could not init FreeType Library");

	FT_Face face;

	path resPath = fontPath;
	std::string finalPath;
	std::string fontName = resPath.filename().string();

	if (resPath.is_absolute()) {
		//Copy to local directory
		fontPath = "/fonts/" + resPath.filename().string();
		finalPath = SimpleEngine::Instance()->GetResourceManager()->GetResourcesBaseDir() + fontPath;
		copy(resPath, finalPath, copy_options::overwrite_existing);
	}
	else
		finalPath = SimpleEngine::Instance()->GetResourceManager()->GetResourcesBaseDir() + fontPath;


	if (FT_New_Face(_fontLib, finalPath.c_str(), 0, &face)) {
		SIMPLE_LOG("FREETYPE: Failed to load font : %s", fontName);
		return false;
	}

	std::vector<SimpleTexture*> toPack;

	//Load the characters for the font
	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Single channel textures
	FontCharacters chars;
	//Compute max char size
	glm::ivec2 maxFontSize = { 1,1 };

	chars.resize(128);
	uint32_t packPadding = 2;
	for (uint8_t c = 0; c < 128; c++) //Currently we only load the first 128 ascii chars
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			SIMPLE_LOG("FREETYTPE: Failed to load Glyph %c", c);
			continue;
		}

		// Generate texture
		SimpleTexture* tex = new SimpleTexture();
		tex->LoadTextureFromMemory(face->glyph->bitmap.buffer, 1, face->glyph->bitmap.width, face->glyph->bitmap.rows, false);
		maxFontSize.x = std::max(maxFontSize.x, (int32_t)face->glyph->bitmap.width);
		maxFontSize.y = std::max(maxFontSize.y, (int32_t)face->glyph->bitmap.rows);

		// Now store character for later use
		chars[c] = {
			c,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		toPack.push_back(tex);
	}
	float scale = 1.0f / (float)std::max(maxFontSize.x, maxFontSize.y);
	_fonts[fontName] = std::make_pair(scale, chars);
	FT_Done_Face(face);
	FT_Done_FreeType(_fontLib);

	//Create spritesheet for font
	SimpleSpriteSheet* packedFont = SimpleUtils::PackTextures(toPack, packPadding);
	packedFont->SetSerializable(false);
	//packedFont->SaveTexture(SimpleEngine::Instance()->GetResourcesBaseDir() + "/fonts/" + FontAtlas.png");
	_spriteSheets[fontName] = packedFont;
	return true;
}
bool SimpleResourceManager::HasFont(SimpleID fontName) {

	return _fonts.find(fontName) != _fonts.end();

}

SimpleResourceManager::FontCharacters SimpleResourceManager::GetFontChars(SimpleID fontName) {

	SIMPLE_ASSERT(HasFont(fontName));
	return _fonts[fontName].second;

}


float SimpleResourceManager::GetFontScale(SimpleID fontName) {

	SIMPLE_ASSERT(HasFont(fontName));
	return _fonts[fontName].first;

}
