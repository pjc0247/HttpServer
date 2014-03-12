#ifndef _KEY_VALUE_CONTAINER
#define _KEY_VALUE_CONTAINER

#include <string>
#include <unordered_map>

template <typename T>
class KeyValueContainer{
public:
	KeyValueContainer(){
	}
	virtual ~KeyValueContainer(){
	}

	void set(const std::string &key,const T &value){
		container[ key ] = value;
	}
	const std::string &get(const T &key){
		auto pair = container.find( key );

		if( pair == container.end() )
			return novalue;

		return pair->second;
	}

	static T novalue;

protected:
	std::unordered_map<std::string,T> container;
};

template <typename T>
T KeyValueContainer<T>::novalue;

#endif //_KEY_VALUE_CONTAINER