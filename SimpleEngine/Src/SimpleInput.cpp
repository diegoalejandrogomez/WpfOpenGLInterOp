#include "stdafx.h"
#include "SimpleInput.h"

SimpleInput::SimpleInput() {

	_mouse = nullptr;
	_keyboard = nullptr;
	_inputSystem = nullptr;

}


SimpleInput::~SimpleInput() {


	if (_inputSystem) {
		if (_mouse) {
			_inputSystem->destroyInputObject(_mouse);
			_mouse = nullptr;
		}

		//if (mKeyboard) {
		//	mInputSystem->destroyInputObject(mKeyboard);
		//	mKeyboard = 0;
		//}

		//if (mJoysticks.size() > 0) {
		//	itJoystick = mJoysticks.begin();
		//	itJoystickEnd = mJoysticks.end();
		//	for (; itJoystick != itJoystickEnd; ++itJoystick) {
		//		mInputSystem->destroyInputObject(*itJoystick);
		//	}

		//	mJoysticks.clear();
		//}

		//// If you use OIS1.0RC1 or above, uncomment this line
		//// and comment the line below it
		//mInputSystem->destroyInputSystem(mInputSystem);
		////mInputSystem->destroyInputSystem();
		//mInputSystem = 0;

		//// Clear Listeners
		//mKeyListeners.clear();
		//mMouseListeners.clear();
		//mJoystickListeners.clear();
	}

}