#ifndef _HTTP_SERVER_H
#define _HTTP_SERVER_H

#include <string>

#include "Server.h"

struct ClientData;

enum HttpMethod{
	HttpGet,
	HttpPost
};

struct HttpRequest{
	HttpMethod method;

	std::string location;
	//Location location;

	std::string host;
	std::string connection;
	std::string accept;
	std::string userAgent;
	std::string acceptEncoding;
	std::string acceptLanguage;
};

class HttpServer : public Server{
public:
	HttpServer(int port);
	virtual ~HttpServer();

	virtual bool onConnect(ClientData &client);
	virtual bool parseRequest(const std::string &request);
	virtual bool parseOption(
		const std::string &option,const std::string &value,
		HttpRequest &header);
};

#endif //_HTTP_SERVER