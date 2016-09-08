#pragma once
#include "SimpleConfiguration.h"

struct _MonoAssembly;
typedef struct _MonoAssembly MonoAssembly;

struct _MonoDomain;
typedef struct _MonoDomain MonoDomain;

class SIMPLE_API SimpleScripting {

public:

	SimpleScripting() {}

	bool Initialize();
	void Shutdown();
	bool LoadAssembly(std::string fileName);

private:
	MonoDomain* _domain;
	MonoAssembly* _mainAssembly;

};
