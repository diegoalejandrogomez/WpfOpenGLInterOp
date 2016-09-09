#pragma once
#include "json.hpp"
#include "SimpleConfiguration.h"

using json = nlohmann::json;

class SIMPLE_API SimpleSerializable {

public:

	virtual json Serialize() { return json{"Serialization", "Not implemented"}; }
	virtual bool Deserialize(const json &layer) { return true; }
	virtual bool Deserialize(const json &node, std::string dir) { return true; }
	virtual void SetSerializable(bool value) { _serializable = value; };
	virtual bool IsSerializable() { return _serializable; };

	private:

		bool _serializable = true;

};
