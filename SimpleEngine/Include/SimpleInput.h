#pragma once

#include "OISMouse.h"
#include "OISKeyboard.h"
#include "OISJoyStick.h"
#include "OISInputManager.h"


class SimpleInput : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener {
public:
	
	SimpleInput();
	virtual ~SimpleInput();
	
	void Initialize(HWND hWnd, bool exclusive);
	void CreateKeyboard(bool buffered = false);
	void CreateMouse(bool buffered = false);
	void CreateJoystics(bool buffered = false);

	void DestroyKeyboard();
	void DestroyMouse();
	void DestroyJoysticks();


	void Capture();

	void AddKeyListener(OIS::KeyListener *keyListener, const std::string& instanceName);
	void AddMouseListener(OIS::MouseListener *mouseListener, const std::string& instanceName);
	void AddJoystickListener(OIS::JoyStickListener *joystickListener, const std::string& instanceName);

	void RemoveKeyListener(const std::string& instanceName);
	void RemoveMouseListener(const std::string& instanceName);
	void RemoveJoystickListener(const std::string& instanceName);

	void RemoveKeyListener(OIS::KeyListener *keyListener);
	void RemoveMouseListener(OIS::MouseListener *mouseListener);
	void RemoveJoystickListener(OIS::JoyStickListener *joystickListener);

	void RemoveAllListeners(void);
	void RemoveAllKeyListeners(void);
	void RemoveAllMouseListeners(void);
	void RemoveAllJoystickListeners(void);

	void SetWindowExtents(int width, int height);

	OIS::Mouse*    GetMouse(void);
	OIS::Keyboard* GetKeyboard(void);
	OIS::JoyStick* GetJoystick(unsigned int index);

	int GetNumOfJoysticks(void);

private:
	

	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);

	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

	bool povMoved(const OIS::JoyStickEvent &e, int pov);
	bool axisMoved(const OIS::JoyStickEvent &e, int axis);
	bool sliderMoved(const OIS::JoyStickEvent &e, int sliderID);
	bool buttonPressed(const OIS::JoyStickEvent &e, int button);
	bool buttonReleased(const OIS::JoyStickEvent &e, int button);

	OIS::Mouse        *_mouse;
	OIS::Keyboard     *_keyboard;
	OIS::InputManager *_inputSystem;

	std::vector<OIS::JoyStick*> _joysticks;
	
	std::map<std::string, OIS::KeyListener*> _keyListeners;
	std::map<std::string, OIS::MouseListener*> _mouseListeners;
	std::map<std::string, OIS::JoyStickListener*> _joystickListeners;

};
