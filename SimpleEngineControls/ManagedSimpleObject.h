#pragma once
#include "SimpleObject.h"

public ref class ManagedSimpleObject {
public:
	ManagedSimpleObject();
	~ManagedSimpleObject();

	void SetSimpleObject(SimpleObject* simpleObject) { this->simpleObject = simpleObject; };

	/*property glm::vec3 position
	{
		glm::vec3 get() {
			return _position;
		}

		void set(glm::vec3 position)
		{
			_position = position;
		}
	};*/

	glm::vec2 GetSize();

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

	void SetPosition(glm::vec3& pos);
	void SetSize(glm::vec2& size);
	void SetOrientation(float orientation);

private:
	SimpleObject* simpleObject;
	float _Orientation;
};