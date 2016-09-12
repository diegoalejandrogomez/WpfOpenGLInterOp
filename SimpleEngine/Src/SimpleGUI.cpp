#include "stdafx.h"
#include "SimpleGUI.h"
#include "MyGUI.h"
#include "MyGUI_Gui.h"
#include "MyGUI_OpenGL3Platform.h"
#include "MyGUI_InputManager.h"
#include "SimpleEngine.h"
#include "SimpleDispatcher.h"
using namespace MyGUI;


SimpleGUI::SimpleGUI() {

	

}

SimpleGUI::~SimpleGUI() {

}

void SimpleGUI::Render(float dt) {
	
	if(_platform != nullptr)
		_platform->getRenderManagerPtr()->drawOneFrame();

}
bool SimpleGUI::Initialize() {

	_loader = new SimpleOpenGL3ImageLoader();
	_platform = new OpenGL3Platform();
	_platform->initialise(_loader); 
	SimpleCamera2D* cam = SimpleEngine::Instance()->GetScene()->GetCamera();
	glm::vec2 size = cam->GetViewportSize();
	_platform->getRenderManagerPtr()->setViewSize((int)size.x,(int) size.y);

	_InitResources();

	_gui = new Gui();
	_gui->initialise();

	
	

	//Register to input system
	SimpleInput* input = SimpleEngine::Instance()->GetInput();
	input->AddKeyListener(this, "GUI");
	input->AddMouseListener(this, "GUI");


	SimpleDispatcher::Instance()->AddListener(WindowResizeEvent::descriptor, {
		this,
		[this](const SimpleEvent& evt) {
		const WindowResizeEvent &res = static_cast<const WindowResizeEvent&>(evt);
		_platform->getRenderManagerPtr()->setViewSize(res.width, res.height);	
	}
	});
	
	return true;
}
void SimpleGUI::Shutdown() {

	//Unregister from input system
	SimpleInput* input = SimpleEngine::Instance()->GetInput();
	input->RemoveKeyListener(this);
	input->RemoveMouseListener(this);

	_gui->shutdown();
	delete _gui;
	_gui = nullptr;
	_platform->shutdown();
	_platform;
	_platform = nullptr;
}


void SimpleGUI::PushWindow(SimpleWindow* w){
	
	w->Load();
	w->Initialize();
	_windows.push(w);

	if (w->IsModal()) {
		InputManager::getInstancePtr()->addWidgetModal(w->GetRootControl());
	}
}

void SimpleGUI::PopWindow(bool destroy) {

	SimpleWindow * w = _windows.top();
	w->Shutdown();
	
	if (destroy) {
		w->Unload();
		delete w;
	}
	_windows.pop();

}


SimpleWindow* SimpleGUI::GetTopWindow() {
	
	if (_windows.empty())
		return nullptr;

	SimpleWindow *wnd = _windows.top();
	return wnd;
}

bool SimpleGUI::LoadLayout(std::string layout) {
		
	
	//MyGUI::ButtonPtr button = mGUI->findWidget<MyGUI::Button>("MyFirstButton");
	//auto lambda = [](Widget* w) { SIMPLE_LOG("LALALALLA");};
	//
	//// set callback
	//button->eventMouseButtonClick += newDelegate<Widget*>(lambda);

	//button->setCaption("Touch me");

	
	
	return true;

}


void SimpleGUI::_InitResources() {

	_platform->getDataManagerPtr()->addResourceLocation( SimpleEngine::Instance()->GetResourceManager()->GetResourcesBaseDir() + "/gui/", true);

}


bool SimpleGUI::keyPressed(const OIS::KeyEvent &arg) {
	return MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
}
bool SimpleGUI::keyReleased(const OIS::KeyEvent &arg) {
	return MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
}
bool SimpleGUI::mouseMoved(const OIS::MouseEvent &arg) {
	return MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
}
bool SimpleGUI::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}
bool SimpleGUI::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return MyGUI::InputManager::getInstance().injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}