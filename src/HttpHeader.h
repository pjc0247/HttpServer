#ifndef _HTTP_HEADER_H
#define _HTTP_HEADER_H

#include <string>

#include "StringContainer.h"

class HttpHeader{
public:
	HttpHeader();
	HttpHeader(const std::string &header);
	virtual ~HttpHeader();

	const std::string &getField(const std::string &name);
	void setField(const std::string &name, const std::string &value);

	bool load(const std::string &header);
	std::string compile();

protected:
	StringContainer data;
};

#endif //_HTTP_HEADER_H