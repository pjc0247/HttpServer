#ifndef _HTTP_SERVER_H
#define _HTTP_SERVER_H

#include <string>

#include "Server.h"
#include "HttpProtocol.h"

struct ClientData;


struct HttpRequest{
	HttpMethod method;

	std::string version;
	std::string location;
	//Location location;

	std::string host;
	std::string connection;
	std::string accept;
	std::string userAgent;
	std::string acceptEncoding;
	std::string acceptLanguage;
};
struct HttpResponse{
	HttpResponseCode status;

	std::string version;
	std::string server;
	std::string connectionType;

	unsigned long contentLength;
};

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