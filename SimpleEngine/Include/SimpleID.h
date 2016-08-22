#pragma once
#include <string>
#include <map>
#include "SimpleConfiguration.h"

//This configures if the hash has hash->string functionality

#define HASH_DB
class SIMPLE_API SimpleID {

public:
	
	typedef uint32_t Type;

	SimpleID(const char* name) {
		_getHash(std::move(name));
	}

	SimpleID(const std::string && name) {
		_getHash(std::move(name));
	}
	SimpleID(const std::string & name) {
		_getHash(std::move(name));
	}

	SimpleID(const SimpleID & id) {
		_id = id._id;
	}

	SimpleID(const SimpleID::Type id) {
		_id = id;
	}

	bool operator==(const SimpleID& other) const {
		return _id == other._id;
	};
	bool operator<(const SimpleID& other) const{
		return _id <  other._id;
	};

	operator Type() const { return _id; }

	SimpleID& operator=(const Type id) {
		_id = id;
		return *this;
	}

#ifdef HASH_DB
	const std::string& GetString()const { return GetHashDB()[_id]; }
	const bool HasString() { return true; };
#else
	const bool HasString() { return false; };
#endif //HASH_DB
private:

	inline void _getHash(const std::string &&name) {
		_id = std::hash<std::string>{}(name);
#ifdef HASH_DB //Check if no collition happens in debug mode
		auto it = GetHashDB().find(_id);
		if(it != GetHashDB().end()) //check the hashes match
			assert(it->second == name);
		else
			GetHashDB()[_id] = name;
#endif // HASH_DB	
	};

	uint32_t _id;

#ifdef HASH_DB
	static std::map<uint32_t, std::string>& GetHashDB() {
		static std::map<uint32_t, std::string> hashDB;
		return hashDB;
	}
	
#endif // HASH_DB

};

//Hash function 
namespace std {
	template <> struct hash<SimpleID>
	{
		size_t operator()(const SimpleID & x) const
		{
			return (size_t)x;
		}
	};
}