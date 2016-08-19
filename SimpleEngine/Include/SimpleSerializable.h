#pragma once
#include "json.hpp"
using json = nlohmann::json;

class SimpleSerializable {

public:

	virtual json Serialize() { return json{"Serialization", "Not implemented"}; }
	virtual bool Deserialize(json &layer) { return true; }

	virtual void SetSerializable(bool value) { _serializable = value; };
	virtual bool IsSerializable() { return _serializable; };

	private:

		bool _serializable = true;

};
