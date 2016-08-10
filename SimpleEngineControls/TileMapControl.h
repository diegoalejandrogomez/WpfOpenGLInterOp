#pragma once
#include "TileEditorApp.h"

namespace SimpleEngineControls {
	public ref class TileMapControl
	{
	private:
		TileEditorApp* _app = nullptr;
	public:
		
		TileMapControl();
		~TileMapControl();

		//Properties

		property int MapWidth
		{
			int get() {
				if (_app == nullptr)
					return 0;
				return _app->GetMapWidth();
			}

			void set(int width)
			{
				if (_app != nullptr)
					_app->SetMapWidth(width);
			}
		};

		property int MapHeight
		{
			int get() {
				if (_app == nullptr)
					return 0;
				return _app->GetMapHeight();
			}

			void set(int height)
			{
				if (_app != nullptr)
					_app->SetMapHeight(height);
			}
		};

	};
}
