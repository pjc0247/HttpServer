#include "stdafx.h"

#include <functional>
#include <string>
#include <thread>
#include <regex>
#include <algorithm>

#include "Server.h"
#include "HttpServer.h"

#include "ReasonPhraseTable.h"

using namespace std;

const char DoubleCrLf[] = "\r\n\r\n";
const char CrLf[] = "\r\n";

HttpServer::HttpServer(int port) :
	Server(port) {

	this->HttpServer::HttpServer( "TinyHttpServer", port );
}
HttpServer::HttpServer(
	const string &serverName, int port) :
	Server(port) {

	setServerName( serverName );
}
HttpServer::~HttpServer(){
}

int HttpServer::sendString(SOCKET socket, const string &str){
	int sent;

	sent = ::send(socket, (char*)str.c_str(), str.length(), 0);

	return sent;
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
				DoubleCrLf) ){
			break;
		}
	}

	printf("\n\n%s|\n", request.c_str());

	parseRequest(request);

	sendResponse( 
		client.socket,
		HttpResponseCode::StatusOk, "okhello" );

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

string HttpServer::compileHeader(HttpResponse &response){
	string header;

	ReasonPhraseTable *ptable = ReasonPhraseTable::getInstance();

	char status[8];
	_itoa( response.status, status, 10 );

	/* HttpVer / StatusCode / ReasonPhrase */
	header += response.version + " ";
	header += string(status) + " ";
	header += ptable->getPhrase(response.status) + CrLf;
	

	/* Server */
	header += "Server:" + response.server + CrLf;

	/* Content-length */
	char contentLength[32];
	_ultoa( response.contentLength, contentLength, 10 );
	header += "Content-length:" + string(contentLength) + CrLf;


	/* CrLf */
	header += CrLf;

	return header;
}
bool HttpServer::sendResponse(
	SOCKET socket,
	HttpResponseCode code, const string &document){


	HttpResponse response;

	response.server = getServerName();
	response.contentLength = document.length();
	response.status = HttpResponseCode::StatusOk;
	response.version = HttpVersion11;

	auto &header = compileHeader(response);

	sendString( socket, header );
	sendString( socket, document );

	return true;
}

void HttpServer::setServerName(const string &_serverName){
	serverName.assign( _serverName );
}
string &HttpServer::getServerName(){
	return serverName;
}