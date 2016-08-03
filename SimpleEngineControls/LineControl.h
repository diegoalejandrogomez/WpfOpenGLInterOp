#pragma once
#include "CoordinatesControl.h"
#include "BaseControl.h"
#include "Stdafx.h"
namespace SimpleEngineControls {
	public ref class LineControl : public BaseControl
	{
	public:
		LineControl();
		LineControl(CoordinatesControl^, CoordinatesControl^);
		void Draw() override;
		CoordinatesControl^ PointA;
		CoordinatesControl^ PointB;
	};
}