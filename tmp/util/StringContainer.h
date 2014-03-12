#ifndef _STRING_CONTAINER_H
#define _STRING_CONTAINER_H

#include <string>

#include "KeyValueContainer.h"

class StringContainer : public KeyValueContainer<std::string>{
public:
	StringContainer();
	
	bool load(const std::string &str);
};

#endif //_STRING_CONTAINER_H