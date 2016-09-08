#include "stdafx.h"
#include "SimpleScripting.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

bool SimpleScripting::Initialize() {

	mono_set_dirs(".\\lib", ".\\etc");
	_domain = mono_jit_init("SimpleScripting");
	return true;
}


bool SimpleScripting::LoadAssembly(std::string fileName) {
	

	MonoAssembly *assembly;
		
	_mainAssembly = mono_domain_assembly_open(_domain, fileName.c_str());
	if (!assembly) {
		SIMPLE_LOG("Couldn't load assembly: %s", fileName.c_str());
		return false;
	}
	return true;

}
void SimpleScripting::Shutdown() {
	mono_jit_cleanup(_domain);
}
