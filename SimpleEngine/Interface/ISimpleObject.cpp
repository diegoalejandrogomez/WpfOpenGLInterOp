#include "stdafx.h"
#include "ISimpleObject.h"


void SimpleObject_GetPosition(SimpleObject* sObj, float &x, float &y, float &z) {
	glm::vec3 pos= sObj->GetPosition();
	x = pos.x;
	y = pos.y;
	z = pos.z;

}

void SimpleObject_GetX(SimpleObject* sObj, float &x) {
	glm::vec3 pos = sObj->GetPosition();
	x = pos.x;
	
}
SIMPLE_API void SimpleObject_GetY(SimpleObject* sObj, float &y) {

	glm::vec3 pos = sObj->GetPosition();
	y = pos.y;

}
SIMPLE_API void SimpleObject_GetZ(SimpleObject* sObj, float &z) {

	glm::vec3 pos = sObj->GetPosition();
	z = pos.z;
}


void SimpleObject_GetSize(SimpleObject* sObj, float &width, float &height){

	glm::vec2 size = sObj->GetSize();
	width = size.x;
	height = size.y;
	
}

void SimpleObject_GetWidth(SimpleObject* sObj, float &width) {
	width = sObj->GetSize().x;
}

void SimpleObject_GetHeight(SimpleObject* sObj, float &height) {
	height = sObj->GetSize().y;
}

void SimpleObject_GetOrientation(SimpleObject* sObj, float &orientation) {

	orientation = sObj->GetOrientation();
}
uint32_t SimpleObject_GetName(SimpleObject* sObj) {
	return sObj->GetName();
}

void SimpleObject_SetPosition(SimpleObject* sObj, float x, float y, float z) {
	sObj->SetPosition({ x,y,z });
}

void SimpleObject_SetX(SimpleObject* sObj, float x) {
	sObj->SetPosition({ x , sObj->GetPosition().y, sObj->GetPosition().z });

}
void SimpleObject_SetY(SimpleObject* sObj, float y) {

	sObj->SetPosition({ sObj->GetPosition().x, y, sObj->GetPosition().z });

}
void SimpleObject_SetZ(SimpleObject* sObj, float z) {

	sObj->SetPosition({  sObj->GetPosition().x, sObj->GetPosition().y, z });

}


void SimpleObject_SetSize(SimpleObject* sObj, float width, float height) {
	sObj->SetSize({ width, height });
}

void SimpleObject_SetWidth(SimpleObject* sObj, float width) {
	sObj->SetSize({ width, sObj->GetSize().y });
}
void SimpleObject_SetHeight(SimpleObject* sObj, float height) {

	sObj->SetSize({ sObj->GetSize().x, height });

}

void SimpleObject_SetOrientation(SimpleObject* sObj, float orientation) {
	sObj->SetOrientation(orientation);
}
void SimpleObject_SetName(SimpleObject* sObj, const char* name) {
	sObj->SetName(name);
}
uint32_t SimpleObject_GetType(SimpleObject* sObj) {
	return sObj->GetType();
}

const char* SimpleObject_GetStringName(SimpleObject* sObj) {
	return sObj->GetName().GetString().c_str();
	
}