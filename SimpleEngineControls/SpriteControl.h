#pragma once
#include "SimpleObject.h"
#include "SimpleSpriteRenderer.h"
#include "SimpleLayer.h";

namespace SimpleEngineControls {
	public ref class SpriteControl
	{
		private:
			SimpleSpriteRenderer* _simpleSpriteRenderer;
			SimpleLayer* _simpleLayer;
		public:
			SpriteControl();
			~SpriteControl();
			void AddControl(System::String^ path); //, glm::vec3 _position,glm::vec2 _size);

	};
}