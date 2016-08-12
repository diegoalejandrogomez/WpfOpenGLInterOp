#pragma once
#include "SimpleSpriteSheetRenderer.h"
#include "SimpleLayer.h"
#include "ManagedSimpleObject.h"

namespace SimpleEngineControls {
	public ref class SpriteSheetControl
	{
	private:
		SimpleSpriteSheetRenderer* _simpleSpriteSheetRenderer;
		ManagedSimpleObject^ _managedSimpleObject;
	public:
		ManagedSimpleObject^ GetManagedSimpleObject();
		SpriteSheetControl();
		~SpriteSheetControl();
		void AddControl(System::String^ path, int x, int y, int w, int h);

		property float positionX
		{
			float get() {
				if (this->_simpleSpriteSheetRenderer == nullptr)
					return 0;
				return _simpleSpriteSheetRenderer->GetPosition().x;
			}

			void set(float position)
			{
				_simpleSpriteSheetRenderer->SetPosition(glm::vec3(position, _simpleSpriteSheetRenderer->GetPosition().y, _simpleSpriteSheetRenderer->GetPosition().z));
			}
		};

		property float positionY
		{
			float get() {
				if (this->_simpleSpriteSheetRenderer == nullptr)
					return 0;
				return _simpleSpriteSheetRenderer->GetPosition().y;
			}

			void set(float position)
			{
				_simpleSpriteSheetRenderer->SetPosition(glm::vec3(_simpleSpriteSheetRenderer->GetPosition().x, position, _simpleSpriteSheetRenderer->GetPosition().z));
			}
		};

		property float heigth
		{
			float get() {
				if (this->_simpleSpriteSheetRenderer == nullptr)
					return 0;
				return _simpleSpriteSheetRenderer->GetSize().y;
			}

			void set(float heigth)
			{
				_simpleSpriteSheetRenderer->SetSize(glm::vec2(_simpleSpriteSheetRenderer->GetSize().x, heigth));
			}
		};

		property float width
		{
			float get() {
				if (this->_simpleSpriteSheetRenderer == nullptr)
					return 0;
				return _simpleSpriteSheetRenderer->GetSize().x;
			}

			void set(float width)
			{
				_simpleSpriteSheetRenderer->SetSize(glm::vec2(width, _simpleSpriteSheetRenderer->GetSize().y));
			}
		};

	};
}