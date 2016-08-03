#include "stdafx.h"
#include "BaseControl.h"

using namespace SimpleEngineControls;

BaseControl^ BaseControl::GetInfo(){
	return this;
}

void BaseControl::SetColor(std::string color){
	Color = gcnew System::String(color.c_str());

}

System::String^ BaseControl::GetColor() {
	return Color;
}