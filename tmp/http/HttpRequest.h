#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

#include "HttpProtocol.h"

#include "Location.h"

class HttpRequest{
public:
	HttpRequest();
	HttpRequest(const std::string &header);
	HttpRequest(const std::string &header, const std::string &document);
	virtual ~HttpRequest();

	const string &getHeader();
	const string &getDocument();

	HttpMethod getHttpMethod();
	void setHttpMethod(HttpMethod method);

	const std::string &getHttpVersion();
	void setHttpVersion(const std::string &httpver);

	Location &getLocation();

	const std::string &getHost();
	void setHost(const std::string &host);

	const std::string &getConnection();
	void setConnection(const std::string &connection);

	const std::string &getAccept();
	void setAccept(const std::string &accept);

	const std::string &getUserAgent();
	void setUserAgent(const std::string &userAgent);

	const std::string &getAcceptEncoding();
	void setAcceptEncoding(const std::string &acceptEncoding);

	const std::string &getAcceptLanguage();
	void setAcceptLanguage(const std::string &acceptLanguage);

protected:
	void setHeader(const std::string &header);
	void setDocument(const std::string &document);

	bool parse();
	bool parseOption(const std::string &key,const std::string &value);

protected:
	std::string header;
	std::string document;

	HttpMethod method;

	std::string version;
	Location location;

	std::string host;
	std::string connection;
	std::string accept;
	std::string userAgent;
	std::string acceptEncoding;
	std::string acceptLanguage;
};

#endif //_HTTP_REQUEST_H