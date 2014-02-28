#ifndef _HTTP_SERVER_H
#define _HTTP_SERVER_H

#include <string>

#include "Server.h"

#include "HttpProtocol.h"
#include "HttpResponse.h"
#include "HttpRequest.h"

#include "Location.h"

struct ClientData;
class Handler;

class HttpServer : public Server{
public:
	HttpServer(int port);
	HttpServer(
		const std::string &serverName,int port);

	virtual ~HttpServer();

	void setServerName(const std::string &name);
	std::string &getServerName();

protected:
	virtual bool onConnect(ClientData &client);

	virtual int sendString(SOCKET socket, const std::string &str);

	virtual bool parseRequest(const std::string &request);
	virtual bool parseOption(
		const std::string &option,const std::string &value,
		HttpRequest &header);

	virtual std::string compileHeader(HttpResponse &response);
	virtual bool sendResponse(
		SOCKET socket,
		HttpResponseCode code, const std::string &document);
	

protected:
	std::string serverName;
};

#endif //_HTTP_SERVER