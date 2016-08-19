#pragma once
#include "json.hpp"
using json = nlohmann::json;

class SimpleSerializable {

public:

	virtual json Serialize() = 0;
	virtual bool Deserialize(json &layer) = 0;

	virtual void SetSerializable(bool value) { _serializable = value; };
	virtual bool IsSerializable() { return _serializable; };

	private:

		bool _serializable = true;

};
