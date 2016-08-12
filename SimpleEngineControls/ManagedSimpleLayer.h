#pragma once
#include "SimpleObject.h"
#include "SimpleEngine.h"
#include "ManagedSimpleObject.h"
using namespace System::Runtime::InteropServices;

public ref class ManagedSimpleLayer {
public:
	ManagedSimpleLayer(SimpleLayer *simpleLayer);

	~ManagedSimpleLayer();

	property float Z
	{
		float get() {
			return simpleLayer->GetZ();
		}

		void set(float value)
		{
			simpleLayer->SetZ(value);
		}
	};

	property System::String^ Name
	{
		System::String^ get() {
			return gcnew System::String(simpleLayer->GetName().GetString().c_str());

		}

		void set(System::String^ name)
		{
			const char* cstr = (const char*)(Marshal::StringToHGlobalAnsi(name)).ToPointer();
			std::string sstr = cstr;
			Marshal::FreeHGlobal(System::IntPtr((void*)cstr));

			simpleLayer->SetName(sstr);
		}
	};

	property System::Collections::Generic::List<ManagedSimpleObject^>^ SimpleObjects
	{
		System::Collections::Generic::List<ManagedSimpleObject^>^ get() {
			return _simpleObjects;
		}

		void set(System::Collections::Generic::List<ManagedSimpleObject^>^ simpleObjects)
		{
			_simpleObjects = simpleObjects;
		}
	};
private:
	System::Collections::Generic::List<ManagedSimpleObject^>^ _simpleObjects;
	SimpleLayer* simpleLayer;
};