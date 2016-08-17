#include "Stdafx.h"
#include "SimpleEngineViewerControl.h"
#include <SimpleEngine.h>
#include <SimpleRenderer.h>
#include "ManagedSimpleObject.h"
using namespace SimpleEngineControls;



SimpleEngineViewerControl::SimpleEngineViewerControl() {
	this->Load += gcnew System::EventHandler(this, &SimpleEngineViewerControl::OnLoad);
	this->SizeChanged += gcnew System::EventHandler(this, &SimpleEngineViewerControl::OnSizeChanged);
}


void SimpleEngineViewerControl::OnLoad(System::Object ^sender, System::EventArgs ^e){
	
}	

void SimpleEngineViewerControl::Initialize() {

	HWND  _hWnd = (HWND) this->Handle.ToPointer();
	SimpleEngine* eng = SimpleEngine::Instance();
	eng->InitRenderer(_hWnd, Width, Height);
	eng->InitInput((HWND)WPFWindowHandle.ToPointer(), false);
	eng->Initialize();

	_appLogic = new TileEditorApp();
	SimpleEngine::Instance()->SetGameLogic(_appLogic);
	
	OnEngineInitialized(this, EventArgs::Empty);
}

void SimpleEngineViewerControl::OnSizeChanged(System::Object ^sender, System::EventArgs ^e){
	
	SimpleEngine* eng = SimpleEngine::Instance();
	SimpleRenderer* render = eng->GetRenderer();
	if (render != nullptr) {
		render->ResizeWindow(Width, Height);
	}

	//System::Diagnostics::Debug::WriteLine("OnSizeChanged");
}


void SimpleEngineViewerControl::SetMousePosition(float x, float y) {

	glm::vec2 worldPos = SimpleEngine::Instance()->GetScene()->GetCamera()->ScreenToWorld({ x, y });
	_appLogic->SetCursorPosition(worldPos.x, worldPos.y);

}

void SimpleEngineViewerControl::OnPaintBackground(PaintEventArgs^ e)  {

}

void SimpleEngineViewerControl::OnPaint(PaintEventArgs^ e)  {
	
	SimpleEngine::Instance()->Advance(0.0f);
	SimpleEngine::Instance()->Render(0.0f);
	//System::Diagnostics::Debug::WriteLine("OnPaint");

}

void SimpleEngineViewerControl::Paint() {
	if(_appLogic!= nullptr)
		_appLogic->Paint();
}

ManagedSimpleObject^ SimpleEngineViewerControl::SetItem(float x, float y)
{
	glm::vec2 worldPos = SimpleEngine::Instance()->GetScene()->GetCamera()->ScreenToWorld({ x, y });

	SimpleObject* res = SimpleEngine::Instance()->GetScene()->PickFirst({ (float)worldPos.x, worldPos.y });
	SimpleObject *sprite = dynamic_cast<SimpleObject*>(res);
	if (sprite != nullptr) {
		ManagedSimpleObject^ SelectedObject = gcnew ManagedSimpleObject();
		SelectedObject->SetSimpleObject(sprite);
		return SelectedObject;
	}

	return nullptr;
}

System::Collections::Generic::List<ManagedSimpleObject^>^ SimpleEngineViewerControl::GetAllTiles()
{
	System::Collections::Generic::List<ManagedSimpleObject^>^ managedSimpleObjects = gcnew System::Collections::Generic::List<ManagedSimpleObject^>();
	for (SimpleLayer* layer : SimpleEngine::Instance()->GetScene()->GetLayers()) {
		for (SimpleObject* obj : layer->GetEntities()) {
			auto simpleObject = gcnew ManagedSimpleObject();
			simpleObject->SetSimpleObject(obj);
			managedSimpleObjects->Add(simpleObject);
		}
	}

	return managedSimpleObjects;
}

//Move deltas in screen space... This methods translates 'em to world space
void SimpleEngineViewerControl::MoveCamera(float dx, float dy) {
	
	glm::vec2 worldPos = SimpleEngine::Instance()->GetScene()->GetCamera()->ScreenToWorld({ dx, dy });
	glm::vec2 worldOrigin = SimpleEngine::Instance()->GetScene()->GetCamera()->ScreenToWorld({ 0, 0 });
	glm::vec2 delta = worldPos - worldOrigin;
	SimpleEngine::Instance()->GetScene()->GetCamera()->Move(delta.x, -delta.y);

}
void SimpleEngineViewerControl::DeltaZoom(float dz){

	SimpleEngine::Instance()->GetScene()->GetCamera()->DeltaZoom(dz);
}

float SimpleEngineViewerControl::GetZoom() {
	return SimpleEngine::Instance()->GetScene()->GetCamera()->GetZoom();
}

void SimpleEngineViewerControl::SetZoom(float z) {
	SimpleEngine::Instance()->GetScene()->GetCamera()->SetZoom(z);
}


