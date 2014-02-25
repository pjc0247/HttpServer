#ifndef _ENCODING_H
#define _ENCODING_H

#include <string>

class Encoding{
public:
	static Encoding *getInstance();
	static void releaseInstance();

	static Encoding *instance;

protected:
	Encoding();
	virtual ~Encoding();

public:
	//http://www.silverwolf.co.kr/4890
	std::string decodeURL(const std::string &str);
	std::string encodeURL(const std::string &str);
};

#endif //_ENCODING_H