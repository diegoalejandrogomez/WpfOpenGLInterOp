#pragma once

namespace SimpleEngineControls {
	public ref class CoordinatesControl
	{
	public:
		CoordinatesControl();
		CoordinatesControl(float, float);
		float GetX();
		float GetY();
		void SetX(float);
		void SetY(float);
	private:
		float X;
		float Y;
	};
}
