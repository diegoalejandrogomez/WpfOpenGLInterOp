#pragma once
#include "SimpleObject.h"
#include <string>

public ref class ManagedSimpleObject {
public:
	ManagedSimpleObject();
	~ManagedSimpleObject();

	void SetSimpleObject(SimpleObject* simpleObject) { this->simpleObject = simpleObject; };

	property float positionX
	{
		float get() {
			return simpleObject->GetPosition().x;
		}

		void set(float position)
		{
			simpleObject->SetPosition(glm::vec3(position, simpleObject->GetPosition().y, simpleObject->GetPosition().z));
		}
	};

	property float positionY
	{
		float get() {
			return simpleObject->GetPosition().y;
		}

		void set(float position)
		{
			simpleObject->SetPosition(glm::vec3(simpleObject->GetPosition().x, position, simpleObject->GetPosition().z));
		}
	};

	property float positionZ
	{
		float get() {
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