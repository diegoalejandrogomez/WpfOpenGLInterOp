#include "Stdafx.h"
#include "TileMapControl.h"
#include "SimpleEngine.h"

using namespace SimpleEngineControls;

TileMapControl::TileMapControl() {
	_app = dynamic_cast<TileEditorApp*> (SimpleEngine::Instance()->GetGameLogic());
}
TileMapControl::~TileMapControl() {


}
