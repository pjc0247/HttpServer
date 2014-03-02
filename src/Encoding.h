#ifndef _ENCODING_H
#define _ENCODING_H

#include <string>

#include "ThreadSafeSingleton.h"

//typedef std::basic_string<unsigned char> utf8string;
typedef std::string utf8string;

class Encoding : public ThreadSafeSingleton<Encoding>{
private:
	friend ThreadSafeSingleton;

	Encoding();
	virtual ~Encoding();

public:
	//http://www.silverwolf.co.kr/4890
	utf8string encodeUTF8(const std::string &str);
	std::string decodeUTF8(const utf8string &str);

	std::string encodeURL(const utf8string &str);
	utf8string decodeURL(const std::string &str);

private:
	int hex2int(char h);
};

#endif //_ENCODING_H