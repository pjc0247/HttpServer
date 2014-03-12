#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include "HttpProtocol.h"

#include <string>

class HttpResponse{
public:
	HttpResponse();
	virtual ~HttpResponse();


	const std::string getHeader();

	HttpResponseCode getStatusCode();
	void setStatusCode(HttpResponseCode status);

	const std::string &getHttpVersion();
	void setHttpVersion(const std::string &httpver);

	const std::string &getServerName();
	void setServerName(const std::string &server);

	const std::string &getConnectionType();
	void setConnectionType(const std::string &connectionType);

	const std::string &getContentType();
	void setContentType(const std::string &contentType);

	const std::string &getDocument();
	void setDocument(const std::string &document);

	unsigned long getContentLength();


	bool compile();
protected:

protected:
	std::string header;

	HttpResponseCode status;

	std::string version;
	std::string server;
	std::string connectionType;

	std::string contentType;

	std::string document;

	unsigned long contentLength;
};

# endif //_HTTP_RESPONSE_H