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

using namespace std;

const char DoubleCrLf[] = "\r\n\r\n";
const char CrLf[] = "\r\n";

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

	//printf("\n\n%s|\n", request.c_str());

	requestCounter.fetch_add(1);

	parseRequest(request);

	sendResponse( 
		client.socket,
		HttpResponseCode::StatusOk, "<h1>it works!</h1>" );

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
		*dest = move( value );
		return true;
	}
	else return false;
}
bool HttpServer::parseRequest(const string &_request){
	regex expr("([a-zA-Z_-]*)\\s?:\\s?(.*)");
	smatch match;
	string request;

	HttpRequest header;

	request = move( _request );

	/* Method Location HttpVer */
	vector<string> token;
	auto start = request.begin();
	for(auto it=request.begin();it!=request.end();++it){
		if( *it == ' ' || *it == '\r' ){
			string tmp;
			copy( start, it, back_inserter( tmp ) );
			token.push_back( tmp );

			start = ++it;
		}
		if( *it == '\n' )
			break;
	}

	auto &method = token[0];
	transform( method.begin(),method.end(), method.begin(), ::tolower );

	if( method == "get" ) 
		header.method = HttpMethod::HttpGet;
	else if( method == "post" ) 
		header.method = HttpMethod::HttpPost;

	auto &location = token[1];
 	header.location = new Location( location );

	auto &httpver = token[2];
	header.version = move( httpver );

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
	sprintf(status, "%d", response.status);

	/* HttpVer / StatusCode / ReasonPhrase */
	header += response.version + " ";
	header += string(status) + " ";
	header += ptable->getPhrase(response.status) + CrLf;
	

	/* Server */
	header += "Server:" + response.server + CrLf;

	/* Content-length */
	char contentLength[32];
	sprintf(contentLength, "%ul", response.contentLength);
	header += "Content-length:" + string(contentLength) + CrLf;

	/* Connection */
	header += "Connection:" + response.connectionType + CrLf;


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
	response.connectionType = "close";

	auto header = compileHeader(response);

	sendString( socket, header );
	sendString( socket, document );

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
	unsigned int reqs = requestCounter.load();
	return reqs;
}
Router &HttpServer::getRootRouter(){
	return rootRouter;
}