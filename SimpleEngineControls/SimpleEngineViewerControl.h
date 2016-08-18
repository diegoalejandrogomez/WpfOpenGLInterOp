#pragma once
using namespace System;
using namespace System::Windows::Forms;
#include "SimpleEngineControls.h"
#include "ManagedSimpleObject.h"
#include "TileEditorApp.h"
#include "ManagedSimpleLayer.h"

namespace SimpleEngineControls {

	public ref class SimpleEngineViewerControl : public UserControl
	{
	public:
		
		property IntPtr WPFWindowHandle;

		SimpleEngineViewerControl();
		void OnLoad(System::Object ^sender, System::EventArgs ^e);
		void OnSizeChanged(System::Object ^sender, System::EventArgs ^e);
		void OnPaintBackground(PaintEventArgs^ e) override;
		void OnPaint(PaintEventArgs^ e) override;
		ManagedSimpleObject^ SetItem(float x, float y);
		System::String^ TakeSnapshot();
		void RestoreSnapshot(System::String^);

		void Paint();
		

		void Initialize();

		void MoveCamera(float dx, float dy);
		void DeltaZoom(float dz);
		float GetZoom();
		void SetZoom(float z);
		void SetMousePosition(float x, float y);
		System::Collections::Generic::List<ManagedSimpleObject^>^ GetAllTiles();

		//Custom events
		event EventHandler^ OnEngineInitialized;
		
		property int MaxZoom {
			int get() {		
				SimpleScene* scene = SimpleEngine::Instance()->GetScene();
				if (scene != nullptr)
					return (int)scene->GetCamera()->GetMaxZoom();			
				return 100;
			}
		}

		property System::Collections::Generic::List<ManagedSimpleLayer^>^ ManagedSimpleLayers
		{
			System::Collections::Generic::List<ManagedSimpleLayer^>^ get() {
				System::Collections::Generic::List<ManagedSimpleLayer^>^ managedSimpleLayers =
					gcnew System::Collections::Generic::List<ManagedSimpleLayer^>();

				if (SimpleEngine::Instance()->GetScene() != nullptr)
				{
					std::vector<SimpleLayer*> simpleLayers = SimpleEngine::Instance()->GetScene()->GetLayers();


					if (simpleLayers.size() != 0)
					{
						for (auto *layer : simpleLayers)
						{
							ManagedSimpleLayer^ newManagedLayer = gcnew ManagedSimpleLayer(layer);
							managedSimpleLayers->Add(newManagedLayer);
						}

					}
				}
				
				return managedSimpleLayers;
			};
			
		};

	private:
		TileEditorApp* _appLogic;
		
	};
}






