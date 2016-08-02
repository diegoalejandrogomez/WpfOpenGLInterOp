#pragma once
using namespace System;
using namespace System::Windows::Forms;
#include "SimpleEngineControls.h"

namespace SimpleEngineControls {

	public ref class SimpleEngineViewerControl : public UserControl
	{
	public:

		SimpleEngineViewerControl() {
				this->Load += gcnew System::EventHandler(this, &SimpleEngineViewerControl::OnLoad);
				this->SizeChanged += gcnew System::EventHandler(this, &SimpleEngineViewerControl::OnSizeChanged);
		}
		void OnLoad(System::Object ^sender, System::EventArgs ^e);
		void OnSizeChanged(System::Object ^sender, System::EventArgs ^e);
		void OnPaintBackground(PaintEventArgs^ e) override;
		void OnPaint(PaintEventArgs^ e) override;
	};
}






