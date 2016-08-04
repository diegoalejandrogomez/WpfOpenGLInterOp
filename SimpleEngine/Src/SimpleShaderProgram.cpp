#include "stdafx.h"
#include "SimpleShaderProgram.h"
#include "SimpleDebug.h"
#include <fstream>
#include <streambuf>
#include "../resource.h"


SimpleShaderProgram::SimpleShaderProgram() {
		
}


bool SimpleShaderProgram::CompileFromFile(std::string vertexShaderPath, std::string fragmentShaderPath) {

	SIMPLE_LOG("Building shader " + vertexShaderPath + ":" + fragmentShaderPath);
	std::string vertexSource = _LoadFile(vertexShaderPath);
	std::string fragmentSource = _LoadFile(fragmentShaderPath);
	
	return CompileFromString(vertexSource, fragmentSource);

}

bool SimpleShaderProgram::CompileFromResource(int vertexResource, int fragmentResource) {
	std::string vertexSource = _LoadResource(vertexResource);
	std::string fragmentSource = _LoadResource(fragmentResource);
	return CompileFromString(vertexSource, fragmentSource);	
}

bool SimpleShaderProgram::CompileFromString(const std::string& vertexSource, const std::string& fragmentSource) {

	//Create an empty vertex shader handle
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Send the vertex shader source code to GL
	const GLchar *source = (const GLchar *)vertexSource.c_str();
	glShaderSource(_vertexShader, 1, &source, 0);

	//Compile the vertex shader
	glCompileShader(_vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(_vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(_vertexShader, maxLength, &maxLength, &infoLog[0]);

		//Log to console
		SIMPLE_LOG(&infoLog[0]);

		//We don't need the shader anymore.
		glDeleteShader(_vertexShader);
		return false;
	}

	//Create an empty fragment shader handle
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Send the fragment shader source code to GL
	source = (const GLchar *)fragmentSource.c_str();
	glShaderSource(_fragmentShader, 1, &source, 0);

	//Compile the fragment shader
	glCompileShader(_fragmentShader);

	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(_fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(_fragmentShader, maxLength, &maxLength, &infoLog[0]);

		//Log to console
		SIMPLE_LOG(&infoLog[0]);

		glDeleteShader(_fragmentShader);
		glDeleteShader(_vertexShader);

		return false;
	}

	return true;
}

bool SimpleShaderProgram::Link() {

		
	//Create a program object.
	_program = glCreateProgram();

	//Attach our shaders to our program
	glAttachShader(_program, _vertexShader);
	glAttachShader(_program, _fragmentShader);

	//Link our program
	glLinkProgram(_program);
		
	GLint isLinked = 0;
	glGetProgramiv(_program, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_program, maxLength, &maxLength, &infoLog[0]);
		
		//Log to console
		SIMPLE_LOG(&infoLog[0]);

		glDeleteProgram(_program);
		glDeleteShader(_vertexShader);
		glDeleteShader(_fragmentShader);

		//Use the infoLog as you see fit.

		//In this simple program, we'll just leave
		return false;
	}

	//Always detach shaders after a successful link.
	glDetachShader(_program, _vertexShader);
	glDetachShader(_program, _fragmentShader);

	return true;
}

void SimpleShaderProgram::Bind() {
	GL_CHECK(glUseProgram(_program));
}

GLuint SimpleShaderProgram::GetLocationFor(const char* name) {
	return glGetUniformLocation(_program, name);
}
std::string SimpleShaderProgram::_LoadFile(std::string filePath) {
	
	std::ifstream t(filePath);
	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve((unsigned int)t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),	std::istreambuf_iterator<char>());

	t.close();

	return str;
}


std::string SimpleShaderProgram::_LoadResource(int resourceName) {

	
	HMODULE handle = GetModuleHandle(NULL);
	HRSRC rc = FindResource(handle, MAKEINTRESOURCE(resourceName), RT_RCDATA);
	HGLOBAL rcData = LoadResource(handle, rc);
	DWORD size = SizeofResource(handle, rc);
	const char* data = static_cast<const char*>(LockResource(rcData));
	return std::string(data);
}

