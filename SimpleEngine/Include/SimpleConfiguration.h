#pragma once
#include <glm\glm.hpp>
#include <map>

#ifdef SIMPLEENGINE_EXPORTS
#define SIMPLE_API __declspec(dllexport)
#define  SIMPLE_TMPL_IMPORT
#else
#define SIMPLE_API __declspec(dllimport)
#define  SIMPLE_TMPL_IMPORT extern
#endif


//GLM exports
SIMPLE_TMPL_IMPORT template struct SIMPLE_API glm::tvec2<float, glm::highp>;
SIMPLE_TMPL_IMPORT template struct SIMPLE_API glm::tvec3<float, glm::highp>;
SIMPLE_TMPL_IMPORT template struct SIMPLE_API glm::tvec4<float, glm::highp>;
SIMPLE_TMPL_IMPORT template struct SIMPLE_API glm::tvec2<int, glm::highp>;
SIMPLE_TMPL_IMPORT template struct SIMPLE_API glm::tvec3<int, glm::highp>;
SIMPLE_TMPL_IMPORT template struct SIMPLE_API glm::tvec4<int, glm::highp>;
SIMPLE_TMPL_IMPORT template struct SIMPLE_API glm::tmat4x4<float, glm::highp>;


//Stl containers
SIMPLE_TMPL_IMPORT template class SIMPLE_API std::map<uint32_t, std::string>;


