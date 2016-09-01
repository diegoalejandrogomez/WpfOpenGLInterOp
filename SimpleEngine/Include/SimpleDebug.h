#pragma once

#include <Windows.h>
#include <string>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

inline void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{		
		char str[1024];				
		std::string f  = "OpenGL error %08x - %s -> File: %s:%d \n";	
		sprintf_s(str, f.c_str(), err , stmt, fname, line); 
		OutputDebugStringA(str);
	}
}

inline void CheckILError(const char* stmt, const char* fname, int line) {
	
	ILenum Error;
	while ((Error = ilGetError()) != IL_NO_ERROR) {

		char str[2048];
		std::string f = "DevIL error %d : %s  - %s -> File: %s:%d \n";
		sprintf_s(str, f.c_str(), Error, iluErrorString(Error), stmt, fname, line);
		OutputDebugStringA(str);

	}
}


#ifdef _DEBUG
#define SIMPLE_LOG(format, ...) \
	{char str[1024];				\
	std::string f = format;		\
	f += " -> File: %s:%d \n";		\
	sprintf_s(str, f.c_str() , __VA_ARGS__, __FILE__, __LINE__); \
	OutputDebugStringA(str);}

#define SIMPLE_ASSERT(test)\
if(! (test) ){					\
	char str[1024];				\
	std::string f = #test;		\
	f += " -> File: %s:%d";		\
	sprintf_s(str, f.c_str(), __FILE__, __LINE__); \
	OutputDebugStringA(str);	\
	__debugbreak();\
}			

#define GL_CHECK(stmt) do { \
stmt; \
CheckOpenGLError(#stmt, __FILE__, __LINE__); \
} while (0)

#define IL_CHECK(stmt) do { \
stmt; \
CheckILError(#stmt, __FILE__, __LINE__); \
} while (0)

#else
#define SIMPLE_ASSERT(test)
#define SIMPLE_LOG(format, ...)
#define GL_CHECK(stmt) stmt
#define IL_CHECK(stmt) stmt
#endif

inline std::string GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}

