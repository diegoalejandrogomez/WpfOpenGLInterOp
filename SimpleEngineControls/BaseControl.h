#pragma once
#include <string>

namespace SimpleEngineControls {
	public ref class BaseControl
	{
	public:
		virtual void Draw() = 0;
		virtual BaseControl^ GetInfo();
		System::String^ GetColor();
		void SetColor(std::string);
	private:
		System::String^ Color;
	};
}