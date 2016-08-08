#pragma once

#include "OISMouse.h"
#include "OISKeyboard.h"
#include "OISJoyStick.h"
#include "OISInputManager.h"


class SimpleInput : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener {
public:
	SimpleInput();
	virtual ~SimpleInput();
	void Initialize();
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

	static SimpleInput* Instance();

private:
	

	bool KeyPressed(const OIS::KeyEvent &e);
	bool KeyReleased(const OIS::KeyEvent &e);

	bool MouseMoved(const OIS::MouseEvent &e);
	bool MousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool MouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

	bool PovMoved(const OIS::JoyStickEvent &e, int pov);
	bool AxisMoved(const OIS::JoyStickEvent &e, int axis);
	bool SliderMoved(const OIS::JoyStickEvent &e, int sliderID);
	bool ButtonPressed(const OIS::JoyStickEvent &e, int button);
	bool ButtonReleased(const OIS::JoyStickEvent &e, int button);

	OIS::Mouse        *_mouse;
	OIS::Keyboard     *_keyboard;
	OIS::InputManager *_inputSystem;

	std::vector<OIS::JoyStick*> _joysticks;
	std::vector<OIS::JoyStick*>::iterator _itJoystick;
	std::vector<OIS::JoyStick*>::iterator _itJoystickEnd;

	std::map<std::string, OIS::KeyListener*> _keyListeners;
	std::map<std::string, OIS::MouseListener*> _mouseListeners;
	std::map<std::string, OIS::JoyStickListener*> _joystickListeners;

	std::map<std::string, OIS::KeyListener*>::iterator _itKeyListener;
	std::map<std::string, OIS::MouseListener*>::iterator _itMouseListener;
	std::map<std::string, OIS::JoyStickListener*>::iterator _itJoystickListener;

	std::map<std::string, OIS::KeyListener*>::iterator _itKeyListenerEnd;
	std::map<std::string, OIS::MouseListener*>::iterator _itMouseListenerEnd;
	std::map<std::string, OIS::JoyStickListener*>::iterator _itJoystickListenerEnd;

};
