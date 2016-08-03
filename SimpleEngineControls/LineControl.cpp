#include "stdafx.h"
#include "LineControl.h"

using namespace SimpleEngineControls;

LineControl::LineControl() {
	this->PointA = gcnew CoordinatesControl();
	this->PointB = gcnew CoordinatesControl();
}

LineControl::LineControl(CoordinatesControl^ pointA, CoordinatesControl^ pointB) {
	this->PointA = pointA;
	this->PointB = pointB;
}

void LineControl::Draw(){
	//todo: complete
}