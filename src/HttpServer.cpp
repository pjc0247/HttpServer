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
	string header;
	string document;
	bool received = false;

	while( !received ){
		char buf[INBUF_SIZE+1];
		int length = recv(client.socket, buf, INBUF_SIZE, false);

		/* 클라이언트로부터 연결 끊김 */
		if( length == -1 ) break;

		buf[length] = '\0';

		header += buf;

		/* \r\n\r\n 수신 -> 수신 종료 */
		int headerLength = header.length();

		if( headerLength >= 3 ){
			const char *cstr = header.c_str();
			int sidx = max( (headerLength - length) - 3, 0 );
			int eidx = headerLength;

			for(int i=sidx;i<eidx;i++){
				int j;
				for(j=0;j<4;j++){
					if( cstr[i+j] != DoubleCrLf[j] )
						break;
				}

				if( j == 4 ){
					received = true;

					document = header.substr( i+4 );
					header = header.erase( i+4 );

					break;
				}
			}
		}
	}

	requestCounter.fetch_add(1);

	//if( ! request.empty() ){
	HttpRequest request( header );

	unsigned long targetLength = request.getContentLength();
	received = false;

	if( targetLength > 0 ){

		while( !received ){
			char buf[INBUF_SIZE+1];
			int length = recv(client.socket, buf, INBUF_SIZE, false);

			/* 클라이언트로부터 연결 끊김 */
			if( length == -1 ) break;

			buf[length] = '\0';

			document += buf;

			if( document.length() >= targetLength ){
				received = true;
			}
		}
		
		//printf("contentLEngth : %lu\n\n", request.getContentLength());
		//printf("%s\n", document.c_str() );
	}

	HttpResponse response;

	response.setConnectionType("close");
	response.setHttpVersion(HttpVersion11);
	response.setStatusCode(HttpResponseCode::StatusOk);
	response.setServerName("hi");
	response.compile();

	//printf("%s\n", request.getHeader());
	response.setDocument("<h1>hi</h1>");
	
	sendResponse( 
		client.socket,
		response);
		//HttpResponseCode::StatusOk, "<h1>it works!</h1>" );
		
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