// HTTPServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


#include <WinSock2.h>
#include <Windows.h>

#include <functional>
#include <string>
#include <thread>
#include <regex>
#include <algorithm>

#include "Server.h"
#include "HttpServer.h"

using namespace std;

HttpServer::HttpServer(int port) :
	Server(port) {

}
HttpServer::~HttpServer(){
}

bool HttpServer::onConnect(ClientData &client){
	string request;

	while( true ){
		char buf[128+1];
		int length = recv(client.socket, buf, 128, false);

		/* 클라이언트로부터 연결 끊김 */
		if( length == -1 ) break;

		buf[length] = '\0';

		request += buf;

		/* \r\n\r\n 수신 -> 수신 종료 */
		if( !strcmp(
				request.c_str() + (request.length()-4),
				"\r\n\r\n") ){
			break;
		}
	}

	printf("\n\n%s|\n", request.c_str());

	parseRequest(request);

	return true;
}

bool HttpServer::parseOption(
	const string &key,const string &value,
	HttpRequest &header){
	
	string *dest = nullptr;

	if( key == "host" )
		dest = &header.host;
	else if( key == "connection" )
		dest = &header.connection;
	else if( key == "accept" )
		dest = &header.accept;
	else if( key == "user-agent" )
		dest = &header.userAgent;
	else if( key == "accept-encoding" )
		dest = &header.acceptEncoding;
	else if( key == "accept-language" )
		dest = &header.acceptLanguage;

	if( dest != nullptr ){
		dest->assign( value );
		return true;
	}
	else return false;
}
bool HttpServer::parseRequest(const string &_request){
	regex expr("([a-zA-Z_-]*)\\s?:\\s?(.*)");
	smatch match;
	string request;

	HttpRequest header;


	request.assign( _request );

	/* 헤더 파싱 */
	while( regex_search( request, match, expr ) ){
		string &key = match[1].str();
		string &value = match[2].str();

		transform( key.begin(),key.end(),key.begin(), ::tolower );
		
		if( !parseOption( key,value, header ) ){
			printError("unknown option");
			printError( key.c_str() );
		}

		request = match.suffix().str();
	}

	return true;
}
