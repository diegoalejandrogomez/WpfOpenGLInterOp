#pragma once
#include "SimpleObject.h"
#include "SimpleEngine.h"
public ref class ManagedSimpleObject {
public:
	ManagedSimpleObject();
	~ManagedSimpleObject();

	void SetSimpleObject(SimpleObject* simpleObject) { this->simpleObject = simpleObject; };

	property float positionX
	{
		float get() {
			if (this->simpleObject == nullptr)
				return 0;
			auto originalPosition = simpleObject->GetPosition().x;
			auto newX = SimpleEngine::Instance()->GetScene()->GetCamera()->WorldToScreen(glm::vec2(originalPosition, 0)).x;
			return newX;
		}

		void set(float position)
		{
			
			auto newPosition = SimpleEngine::Instance()->GetScene()->GetCamera()->ScreenToWorld(glm::vec2(position, simpleObject->GetPosition().y)); 
			simpleObject->SetPosition(glm::vec3(newPosition.x, simpleObject->GetPosition().y, simpleObject->GetPosition().z));
		}
	};

	property float positionY
	{
		float get() {
			if (this->simpleObject == nullptr)
				return 0;
			auto originalPosition = simpleObject->GetPosition().y;
			auto newY = SimpleEngine::Instance()->GetScene()->GetCamera()->WorldToScreen(glm::vec2(0, originalPosition)).y;
			return newY;
		}

		void set(float position)
		{
			auto newPosition = SimpleEngine::Instance()->GetScene()->GetCamera()->ScreenToWorld(glm::vec2(simpleObject->GetPosition().x, position));
			simpleObject->SetPosition(glm::vec3(simpleObject->GetPosition().x, newPosition.y, simpleObject->GetPosition().z));
		}
	};

	property float positionZ
	{
		float get() {
			if (this->simpleObject == nullptr)
				return 0;
			return simpleObject->GetPosition().z;
		}

		void set(float position)
		{
			simpleObject->SetPosition(glm::vec3(simpleObject->GetPosition().x, simpleObject->GetPosition().y, position));
		}
	};

	property float sizeW
	{
		float get() {
			if (this->simpleObject == nullptr)
				return 0;
			return simpleObject->GetSize().x;
		}

		void set(float width)
		{
			simpleObject->SetSize(glm::vec2(width, simpleObject->GetSize().y));
		}
	};

	property float sizeH
	{
		float get() {
			if (this->simpleObject == nullptr)
				return 0;
			return simpleObject->GetSize().y;
		}

		void set(float heigth)
		{
			simpleObject->SetSize(glm::vec2(simpleObject->GetSize().x, heigth));
		}
	};

	property float Orientation
	{
		float get() {
			if (this->simpleObject == nullptr)
				return 0;
			return this->simpleObject->GetOrientation();
		}

		void set(float orientation)
		{
			return simpleObject->SetOrientation(orientation);
		}
	};

private:
	SimpleObject* simpleObject;

};