#pragma once
#include <string>
#include <map>
#include "SimpleDebug.h"

class SimpleID {


public:
	SimpleID(std::string && name) {
		_getHash(std::move(name));
	}
	SimpleID(std::string & name) {
		_getHash(std::move(name));
	}

	SimpleID(const SimpleID & id) {
		_id = id._id;
	}
	bool operator==(const SimpleID& other) const {
		return _id == other._id;
	};
	bool operator<(const SimpleID& other) const{
		return _id <  other._id;
	};

private:

	inline void _getHash(std::string &&name) {
		_id = std::hash<std::string>{}(name);

#ifdef _DEBUG //Check if no collition happens in debug mode
		auto it = _hashDB.find(_id);
		if(it != _hashDB.end()) //check the hashes match
			SIMPLE_ASSERT(it->second == name);
#endif // _DEBUG	
	};

	uint32_t _id;


#ifdef _DEBUG
	static std::map<uint32_t, std::string> _hashDB;
#endif // _DEBUG

};
