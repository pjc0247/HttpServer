#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

#include "HttpProtocol.h"

class Location;

struct HttpRequest{
	HttpMethod method;

	std::string version;
	Location *location;

	std::string host;
	std::string connection;
	std::string accept;
	std::string userAgent;
	std::string acceptEncoding;
	std::string acceptLanguage;

	HttpRequest();
	virtual ~HttpRequest();
};

#endif //_HTTP_REQUEST_H