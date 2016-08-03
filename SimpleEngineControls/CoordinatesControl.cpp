#include "stdafx.h"
#include "CoordinatesControl.h"

using namespace SimpleEngineControls;

CoordinatesControl::CoordinatesControl() {
	X = 0.0f;
	Y = 0.0f;
}

CoordinatesControl::CoordinatesControl(float X, float Y) {
	this->X = X;
	this->Y = Y;
}

float CoordinatesControl::GetX() {
	return X;
}

float CoordinatesControl::GetY()
{
	return Y;
}

void CoordinatesControl::SetX(float X)
{
	this->X = X;
}

void CoordinatesControl::SetY(float Y)
{
	Y = Y;
}

