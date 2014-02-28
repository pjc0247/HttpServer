#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include "HttpProtocol.h"

#include <string>

struct HttpResponse{
	HttpResponseCode status;

	std::string version;
	std::string server;
	std::string connectionType;

	std::string document;

	unsigned long contentLength;
}

#endif //_HTTP_RESPONSE_H