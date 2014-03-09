#include "stdafx.h"

#include <functional>
#include <string>
#include <thread>
#include <regex>
#include <algorithm>

#include "Server.h"
#include "HttpServer.h"
#include "Location.h"

#include "ReasonPhraseTable.h"

#include "Config.h"

using namespace std;

static const char DoubleCrLf[] = "\r\n\r\n";
static const char CrLf[] = "\r\n";

HttpServer::HttpServer(int port){
	 
	this->HttpServer::HttpServer( "TinyHttpServer", port );
}
HttpServer::HttpServer(
	const string &serverName, int port) :
	Server(port), requestCounter(0),
	rootRouter() {

	setServerName( serverName );
}
HttpServer::~HttpServer(){
}

int HttpServer::sendString(SOCKET socket, const string &str){
	int sent;
	
	sent = ::send(socket, (char*)str.c_str(), str.length(), 0);

	totalOut += sent;
	return sent;
}

bool HttpServer::onConnect(ClientData client){
	string request;

	while( true ){
		char buf[INBUF_SIZE+1];
		int length = recv(client.socket, buf, INBUF_SIZE, false);

		/* 클라이언트로부터 연결 끊김 */
		if( length == -1 ) break;

		buf[length] = '\0';

		request += buf;

		/* \r\n\r\n 수신 -> 수신 종료 */
		if( request.length() >= 4 &&
			!strcmp(
				request.c_str() + (request.length()-4),
				DoubleCrLf) ){
			break;
		}
	}

	//printf("\n\n%s|\n", request.c_str());

	requestCounter.fetch_add(1);

	//if( ! request.empty() ){
	HttpRequest header( request );

	/*
	sendResponse( 
		client.socket,
		HttpResponseCode::StatusOk, "<h1>it works!</h1>" );
		*/
	//}
	/*
	rootRouter.route(
		header.location->begin(), header );
		*/ 
	return true;
}

bool HttpServer::sendResponse(
	SOCKET socket, HttpResponse &response){

	sendString( socket, response.getHeader() );
	sendString( socket, response.getDocument() );

	close( socket );

	return true;
}

void HttpServer::setServerName(const string &_serverName){
	serverName = move( _serverName );
}
string &HttpServer::getServerName(){
	return serverName;
}
unsigned int HttpServer::getRequestCount(){
	unsigned int reqs = 
		requestCounter.load( std::memory_order_acquire );

	return reqs;
}
Router &HttpServer::getRootRouter(){
	return rootRouter;
}