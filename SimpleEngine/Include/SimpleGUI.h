#pragma once
#include "SimpleConfiguration.h"
#include "SimpleOpenGL3ImageLoader.h"
#include "OISMouse.h"
#include "OISKeyboard.h"
#include "OISJoyStick.h"
#include "OISInputManager.h"
#include "SimpleInput.h"
#include <stack>
#include "SimpleWindow.h"

namespace MyGUI {
	class Gui;
	class OpenGL3Platform;
};

class SIMPLE_API SimpleGUI : public OIS::KeyListener, public OIS::MouseListener {
	
public:

	SimpleGUI();
	~SimpleGUI();

	bool Initialize();
	void Shutdown();

	//Just for special needs, we shouldn use this method
	bool LoadLayout(std::string layout);
	void Render(float dt);


	void PushWindow(SimpleWindow* w);
	void PopWindow(bool destroy);
private:

	void _InitResources();

	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);


	MyGUI::Gui* _gui;
	MyGUI::OpenGL3Platform* _platform = nullptr;
	SimpleOpenGL3ImageLoader* _loader = nullptr;

	std::stack<SimpleWindow*> _windows ;
};


	
