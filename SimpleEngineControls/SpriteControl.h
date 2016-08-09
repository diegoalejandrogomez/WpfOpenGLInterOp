#pragma once
#include "SimpleObject.h"
#include "SimpleSpriteRenderer.h"
#include "SimpleLayer.h";
#include "ManagedSimpleObject.h"

namespace SimpleEngineControls {
	public ref class SpriteControl
	{
		private:
			SimpleSpriteRenderer* _simpleSpriteRenderer;
			SimpleLayer* _simpleLayer;
			ManagedSimpleObject^ _managedSimpleObject;
		public:
			ManagedSimpleObject^ GetManagedSimpleObject();
			SpriteControl();
			~SpriteControl();
			void AddControl(System::String^ path); //, glm::vec3 _position,glm::vec2 _size);

	};
}