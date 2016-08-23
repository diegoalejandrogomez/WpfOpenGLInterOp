#pragma once
#include "SimpleObject.h"

extern "C" {

	SIMPLE_API void SimpleObject_GetPosition(SimpleObject* sObj,float &x, float &y, float &z);
	SIMPLE_API void SimpleObject_GetX(SimpleObject* sObj, float &x);
	SIMPLE_API void SimpleObject_GetY(SimpleObject* sObj, float &y);
	SIMPLE_API void SimpleObject_GetZ(SimpleObject* sObj, float &z);

	SIMPLE_API void SimpleObject_GetSize(SimpleObject* sObj, float &width, float &height);
	SIMPLE_API void SimpleObject_GetWidth(SimpleObject* sObj, float &width);
	SIMPLE_API void SimpleObject_GetHeight(SimpleObject* sObj, float &height);

	SIMPLE_API void SimpleObject_GetOrientation(SimpleObject* sObj, float &orientation);
	SIMPLE_API uint32_t SimpleObject_GetName(SimpleObject* sObj);

	SIMPLE_API void SimpleObject_SetPosition(SimpleObject* sObj, float x, float y, float z);
	SIMPLE_API void SimpleObject_SetX(SimpleObject* sObj, float x);
	SIMPLE_API void SimpleObject_SetY(SimpleObject* sObj, float y);
	SIMPLE_API void SimpleObject_SetZ(SimpleObject* sObj, float z);

	SIMPLE_API void SimpleObject_SetSize(SimpleObject* sObj, float width, float height);
	SIMPLE_API void SimpleObject_SetWidth(SimpleObject* sObj, float width);
	SIMPLE_API void SimpleObject_SetHeight(SimpleObject* sObj, float height);

	SIMPLE_API void SimpleObject_SetOrientation(SimpleObject* sObj, float orientation);
	SIMPLE_API void SimpleObject_SetName(SimpleObject* sObj, const char* name);

	SIMPLE_API const char* SimpleObject_GetStringName(SimpleObject* sObj);
	

	SIMPLE_API uint32_t SimpleObject_GetType(SimpleObject* sObj);



}