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

		void Initialize();

		//Custom events
		event EventHandler^ OnEngineInitialized;
			
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






