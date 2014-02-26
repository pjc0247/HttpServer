#ifndef _ENCODING_H
#define _ENCODING_H

#include <string>

#include "ThreadSafeSingleton.h"

class Encoding : public ThreadSafeSingleton<Encoding>{
private:
	friend ThreadSafeSingleton;

	Encoding();
	virtual ~Encoding();

public:
	//http://www.silverwolf.co.kr/4890
	std::string decodeURL(const std::string &str);
	std::string encodeURL(const std::string &str);
};

#endif //_ENCODING_H