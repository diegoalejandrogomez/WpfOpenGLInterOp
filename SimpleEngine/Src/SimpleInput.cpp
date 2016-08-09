#include "stdafx.h"
#include "SimpleInput.h"
#include "SimpleEngine.h"

#include <sstream>

SimpleInput::SimpleInput() {

	_mouse = nullptr;
	_keyboard = nullptr;
	_inputSystem = nullptr;

}

void SimpleInput::DestroyKeyboard() {
	if (_keyboard) {
		_inputSystem->destroyInputObject(_keyboard);
		_keyboard = nullptr;
	}
}

void SimpleInput::DestroyMouse() {
	if (_mouse) {
		_inputSystem->destroyInputObject(_mouse);
		_mouse = nullptr;
	}
}

void SimpleInput::DestroyJoysticks() {
	for (auto &joystick : _joysticks)
		_inputSystem->destroyInputObject(joystick);

	_joysticks.clear();
}

SimpleInput::~SimpleInput() {


	if (_inputSystem) {

		DestroyMouse();
		DestroyKeyboard();
		DestroyJoysticks();
	
		_inputSystem->destroyInputSystem(_inputSystem);
		//mInputSystem->destroyInputSystem();
		_inputSystem = nullptr;

		// Clear Listeners
		_keyListeners.clear();
		_mouseListeners.clear();
		_joystickListeners.clear();
		
	}
}


void SimpleInput::Initialize(HWND hWnd, bool exclusive) {

	if (!_inputSystem) {

		SimpleRenderer * render = SimpleEngine::Instance()->GetRenderer();

		// Setup basic variables
		OIS::ParamList paramList;
		std::ostringstream windowHndStr;

		// Fill parameter list
		//windowHndStr << (unsigned int)render->GetWindowHandle();
		windowHndStr << (unsigned int) hWnd;
		paramList.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		/*
		To set coop level use 
		"w32_keyboard", "w32_mouse", "w32_joystick" 
		with the following possible values
		DISCL_BACKGROUND, DISCL_EXCLUSIVE, DISCL_FOREGROUND, DISCL_NONEXCLUSIVE, DISCL_NOWINKEY
		*/
		if (!exclusive)
		{
			paramList.insert(std::make_pair(std::string("w32_keyboard"), "DISCL_NONEXCLUSIVE"));
			paramList.insert(std::make_pair(std::string("w32_keyboard"), "DISCL_FOREGROUND"));
			paramList.insert(std::make_pair(std::string("w32_keyboard"), "DISCL_NOWINKEY"));
			paramList.insert(std::make_pair(std::string("w32_mouse"), "DISCL_NONEXCLUSIVE"));
			paramList.insert(std::make_pair(std::string("w32_mouse"), "DISCL_FOREGROUND"));
			paramList.insert(std::make_pair(std::string("w32_joystick"), "DISCL_NONEXCLUSIVE"));
			paramList.insert(std::make_pair(std::string("w32_joystick"), "DISCL_FOREGROUND"));
		}
		else {
		
			paramList.insert(std::make_pair(std::string("w32_keyboard"), "DISCL_EXCLUSIVE"));
			paramList.insert(std::make_pair(std::string("w32_keyboard"), "DISCL_FOREGROUND"));
			paramList.insert(std::make_pair(std::string("w32_keyboard"), "DISCL_NOWINKEY"));
			paramList.insert(std::make_pair(std::string("w32_mouse"), "DISCL_EXCLUSIVE"));
			paramList.insert(std::make_pair(std::string("w32_mouse"), "DISCL_BACKGROUND"));
			paramList.insert(std::make_pair(std::string("w32_joystick"), "DISCL_EXCLUSIVE"));
			paramList.insert(std::make_pair(std::string("w32_joystick"), "DISCL_BACKGROUND"));

		}
		// Create inputsystem
		_inputSystem = OIS::InputManager::createInputSystem(paramList);
		
	}
}


void SimpleInput::CreateKeyboard(bool buffered) {
	SIMPLE_ASSERT(_inputSystem != nullptr);
	// Create a buffered keyboard
	if (_inputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0) {
		_keyboard = static_cast<OIS::Keyboard*>(_inputSystem->createInputObject(OIS::OISKeyboard, buffered));
		if(buffered)
			_keyboard->setEventCallback(this);
	}
}
void SimpleInput::CreateMouse(bool buffered) {
	SIMPLE_ASSERT(_inputSystem != nullptr);
	SimpleRenderer * render = SimpleEngine::Instance()->GetRenderer();
	// Create buffered mouse
	if (_inputSystem->getNumberOfDevices(OIS::OISMouse) > 0) {
		_mouse = static_cast<OIS::Mouse*>(_inputSystem->createInputObject(OIS::OISMouse, buffered));
		if (buffered)
			_mouse->setEventCallback(this);
		SetWindowExtents(render->GetWidth(), render->GetHeight());
	}
}
void SimpleInput::CreateJoystics(bool buffered) {
	SIMPLE_ASSERT(_inputSystem != nullptr);
	// If possible create all joysticks in buffered mode
	if (_inputSystem->getNumberOfDevices(OIS::OISJoyStick) > 0) {
		//mJoysticks.resize( mInputSystem->numJoySticks() );
		_joysticks.resize(_inputSystem->getNumberOfDevices(OIS::OISJoyStick));

		for (auto &joystick : _joysticks) {
			joystick = static_cast<OIS::JoyStick*>(_inputSystem->createInputObject(OIS::OISJoyStick, buffered));
			if (buffered)
				joystick->setEventCallback(this);

		}
	}
}

void SimpleInput::Capture(void) {
	// Need to capture / update each device every frame
	if (_mouse)
		_mouse->capture();

	if (_keyboard) {
		_keyboard->capture();
	}

	for (auto &joystick : _joysticks) 
		joystick->capture();

}

void SimpleInput::AddKeyListener(OIS::KeyListener *keyListener, const std::string& instanceName) {
	if (_keyboard) {
		auto it = _keyListeners.find(instanceName);
		if (it == _keyListeners.end()) 
			_keyListeners[instanceName] = keyListener;
	}
}

void SimpleInput::AddMouseListener(OIS::MouseListener *mouseListener, const std::string& instanceName) {
	if (_mouse) {
		auto it = _mouseListeners.find(instanceName);
		if (it == _mouseListeners.end()) 
			_mouseListeners[instanceName] = mouseListener;
	}
}

void SimpleInput::AddJoystickListener(OIS::JoyStickListener *joystickListener, const std::string& instanceName) {
	
	if (_joysticks.size() > 0) {
		auto it = _joystickListeners.find(instanceName);
		if (it  == _joystickListeners.end()) 
			_joystickListeners[instanceName] = joystickListener;
	}
}

void SimpleInput::RemoveKeyListener(const std::string& instanceName) {
	auto it  = _keyListeners.find(instanceName);
	if (it != _keyListeners.end())
		_keyListeners.erase(it);
}

void SimpleInput::RemoveMouseListener(const std::string& instanceName) {
	auto it = _mouseListeners.find(instanceName);
	if (it != _mouseListeners.end())
		_mouseListeners.erase(it);
}

void SimpleInput::RemoveJoystickListener(const std::string& instanceName) {
	// Check if item exists
	auto it = _joystickListeners.find(instanceName);
	if (it != _joystickListeners.end())
		_joystickListeners.erase(it);
}

void SimpleInput::RemoveKeyListener(OIS::KeyListener *keyListener) {
	auto it = _keyListeners.begin();
	while (it != _keyListeners.end()) {
		if (it->second == keyListener) {
			_keyListeners.erase(it);
			break;
		}
	}
}

void SimpleInput::RemoveMouseListener(OIS::MouseListener *mouseListener) {
	auto it= _mouseListeners.begin();
	while (it != _mouseListeners.end()) {
		if (it->second == mouseListener) {
			_mouseListeners.erase(it);
			break;
		}
	}
}

void SimpleInput::RemoveJoystickListener(OIS::JoyStickListener *joystickListener) {
	auto it= _joystickListeners.begin();
	while (it != _joystickListeners.end()) {
		if (it->second == joystickListener) {
			_joystickListeners.erase(it);
			break;
		}
	}
}

void SimpleInput::RemoveAllListeners() {
	_keyListeners.clear();
	_mouseListeners.clear();
	_joystickListeners.clear();
}

void SimpleInput::RemoveAllKeyListeners() {
	_keyListeners.clear();
}

void SimpleInput::RemoveAllMouseListeners() {
	_mouseListeners.clear();
}

void SimpleInput::RemoveAllJoystickListeners() {
	_joystickListeners.clear();
}

void SimpleInput::SetWindowExtents(int width, int height) {
	// Set mouse region (if window resizes, we should alter this to reflect as well)
	if (_mouse != nullptr) {
		const OIS::MouseState &mouseState = _mouse->getMouseState();
		mouseState.width = width;
		mouseState.height = height;
	}
}

OIS::Mouse* SimpleInput::GetMouse() {
	return _mouse;
}

OIS::Keyboard* SimpleInput::GetKeyboard() {
	return _keyboard;
}

OIS::JoyStick* SimpleInput::GetJoystick(unsigned int index) {
	// Make sure it's a valid index
	if (index < _joysticks.size()) {
		return _joysticks[index];
	}

	return nullptr;
}

int SimpleInput::GetNumOfJoysticks() {
	// Cast to keep compiler happy ^^
	return (int)_joysticks.size();
}

bool SimpleInput::keyPressed(const OIS::KeyEvent &e) {
	auto it = _keyListeners.begin();
	while (it != _keyListeners.end()) {
		if (it->second->keyPressed(e))
			return true;
		++it;
	}
	return false;
}

bool SimpleInput::keyReleased(const OIS::KeyEvent &e) {

	auto it = _keyListeners.begin();
	while (it != _keyListeners.end()) {
		if (it->second->keyReleased(e))
			return true;
		++it;
	}
	return false;
}

bool SimpleInput::mouseMoved(const OIS::MouseEvent &e) {
	auto it = _mouseListeners.begin();
	while (it != _mouseListeners.end()) {
		if (it->second->mouseMoved(e))
			return true;
		++it;
	}
	return false;
}

bool SimpleInput::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	
	auto it = _mouseListeners.begin();
	while (it != _mouseListeners.end()) {
		if (it->second->mousePressed(e, id))
			return true;
		++it;
	}
	return false;
}

bool SimpleInput::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	auto it = _mouseListeners.begin();
	while (it != _mouseListeners.end()) {
		if (it->second->mouseReleased(e,id))
			return true;
		++it;
	}
	return false;
}

//Truly useful XD
bool SimpleInput::povMoved(const OIS::JoyStickEvent &e, int pov) {
	auto it = _joystickListeners.begin();
	while (it != _joystickListeners.end()) {
		if (it->second->povMoved(e,pov))
			return true;
		++it;
	}
	return false;
}

bool SimpleInput::axisMoved(const OIS::JoyStickEvent &e, int axis) {
	auto it = _joystickListeners.begin();
	while (it != _joystickListeners.end()) {
		if (it->second->axisMoved(e, axis))
			return true;
		++it;
	}
	return false;
}

bool SimpleInput::sliderMoved(const OIS::JoyStickEvent &e, int sliderID) {
	auto it = _joystickListeners.begin();
	while (it != _joystickListeners.end()) {
		if (it->second->sliderMoved(e, sliderID))
			return true;
		++it;
	}
	return false;
}

bool SimpleInput::buttonPressed(const OIS::JoyStickEvent &e, int button) {
	auto it = _joystickListeners.begin();
	while (it != _joystickListeners.end()) {
		if (it->second->buttonPressed(e, button))
			return true;
		++it;
	}
	return false;
}

bool SimpleInput::buttonReleased(const OIS::JoyStickEvent &e, int button) {
	auto it = _joystickListeners.begin();
	while (it != _joystickListeners.end()) {
		if (it->second->buttonReleased(e, button))
			return true;
		++it;
	}
	return false;
}