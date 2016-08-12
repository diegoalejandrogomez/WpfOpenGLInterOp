#pragma once
#include <string>
#include <map>
//This configures if the hash has hash->string functionality
#define HASH_DB
class SimpleID {

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
	bool operator==(const SimpleID& other) const {
		return _id == other._id;
	};
	bool operator<(const SimpleID& other) const{
		return _id <  other._id;
	};

	operator Type() const { return _id; }

#ifdef HASH_DB
	const std::string& GetString()const { return _hashDB[_id]; }
#endif //HASH_DB
private:

	inline void _getHash(const std::string &&name) {
		_id = std::hash<std::string>{}(name);
#ifdef HASH_DB //Check if no collition happens in debug mode
		auto it = _hashDB.find(_id);
		if(it != _hashDB.end()) //check the hashes match
			assert(it->second == name);
		else
			_hashDB[_id] = name;
#endif // HASH_DB	
	};

	uint32_t _id;

#ifdef HASH_DB
	static std::map<uint32_t, std::string> _hashDB;
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