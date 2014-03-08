#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

#include "HttpProtocol.h"

class Location;

class HttpRequest{
public:
	HttpRequest();
	virtual ~HttpRequest();

protected:
	HttpMethod method;

	std::string version;
	Location *location;

	std::string host;
	std::string connection;
	std::string accept;
	std::string userAgent;
	std::string acceptEncoding;
	std::string acceptLanguage;
};

#endif //_HTTP_REQUEST_H