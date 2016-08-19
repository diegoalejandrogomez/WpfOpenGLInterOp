#include "Stdafx.h"
#include "TileMapControl.h"
#include "SimpleEngine.h"
#include <msclr/marshal_cppstd.h>
using namespace System::Runtime::InteropServices;

using namespace SimpleEngineControls;

TileMapControl::TileMapControl() {
	_app = dynamic_cast<TileEditorApp*> (SimpleEngine::Instance()->GetGameLogic());
}
TileMapControl::~TileMapControl() {


}

void TileMapControl::SetBrush(String^ path, Int32 idx) {
	_app->SetCursorTile(msclr::interop::marshal_as<std::string>(path), idx);
}

void TileMapControl::IdleBrush() {
	_app->SetCursorIdle();
}

void TileMapControl::EraseBrush() {
	_app->SetCursorErase();
}

void TileMapControl::Paint() {
	if (_app != nullptr)
		_app->Paint();
}

System::String^ TileMapControl::TakeSnapshot() {
	std::string state = SimpleEngine::Instance()->GetSceneState();
	auto editor = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());

	return gcnew System::String(editor->GetState().c_str());

	//return gcnew System::String(state.c_str());
}

void TileMapControl::RestoreSnapshot(System::String^ state)
{
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(state)).ToPointer();
	auto editor = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	editor->LoadState(chars);
	//auto scene = SimpleEngine::Instance()->SetSceneState(chars);

}