#include "Stdafx.h"
#include "TileMapControl.h"
#include "SimpleEngine.h"
#include <msclr/marshal_cppstd.h>

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