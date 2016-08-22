#pragma once
#include "SimpleID.h"
#include "SimpleConfiguration.h"

#define FACTORY_REGISTER(base, child) \
class child;	\
extern SIMPLE_API base::DerivedRegister<child> _reg ##child (#child);

template <class Base>
class SIMPLE_API SimpleFactory {
	
	template<typename T> 
	static Base * Create() { return new T(); }

public:

	struct BaseFactory {
		typedef std::map<SimpleID, Base*(*)()> constructorMap;

		static Base * CreateInstance(SimpleID s) {
			constructorMap::iterator it = getMap()->find(s);
			if (it == getMap()->end())
				return 0;
			return it->second();
		}

		static constructorMap* getMap() {
			static constructorMap* _map = new constructorMap();
			return _map;
		}

	private:
	
	};

	template<typename T>
	struct DerivedRegister : BaseFactory {
		DerivedRegister(SimpleID s) {
			getMap()->insert(std::make_pair(s, &SimpleFactory::Create<T>));
		}
	};
};

