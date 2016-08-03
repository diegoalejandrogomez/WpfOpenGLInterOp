#pragma once
#include <GL\GL.h>
#include <string>

class SimpleShaderProgram{
public:
	SimpleShaderProgram();

	bool CompileFromFile(std::string vertexShaderPath, std::string fragmentShaderPath);
	bool CompileFromResource(int vertexResource, int fragmentResource);
	bool CompileFromString(const std::string& vertexSource,const std::string& fragmentSource);
	bool Link();

	GLuint GetHandle() { return _program; };
private:

	std::string _LoadFile(std::string filePath);
	std::string _LoadResource(int resourceName);
	GLuint _vertexShader;
	GLuint _fragmentShader;
	GLuint _program;
};