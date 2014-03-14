#include "stdafx.h"

#include "HttpRequest.h"

#include <regex>

using namespace std;

HttpRequest::HttpRequest() :
	location() {
}
HttpRequest::HttpRequest(const std::string &header){
	contentLength = 0;

	setHeader( header );

	parseHeader();
}
HttpRequest::HttpRequest(const std::string &header,const string &document){
	contentLength = 0;

	setHeader( header );
	setDocument( document );

	parseHeader();
	parseDocument();
}

HttpRequest::~HttpRequest(){
}

bool HttpRequest::parseHeader(){
	regex expr("([a-zA-Z_-]*)\\s?:\\s?(.*)");
	smatch match;
	string request;

	request = header;

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
		setHttpMethod( HttpMethod::HttpGet );
	else if( method == "post" ) 
		setHttpMethod( HttpMethod::HttpPost );
	else if( method == "put" ) 
		setHttpMethod( HttpMethod::HttpPut );
	else if( method == "delete" ) 
		setHttpMethod( HttpMethod::HttpDelete );

	/* location */
	location.setRequestURI( token[1] );

	/* HttpVersion */
	setHttpVersion( token[2] );


	/* Options */
	while( regex_search( request, match, expr ) ){
		string key = match[1].str();
		string value = match[2].str();

		transform( key.begin(),key.end(),key.begin(), ::tolower );
		
		if( !parseOption( key,value ) ){
			/* unknown option */
		}

		request = match.suffix().str();
	}

	return true;
}
bool HttpRequest::parseDocument(){
	/* parse post form-data */
	if( getHttpMethod() == HttpMethod::HttpPost ){
		printf("%s\n", getContentType());
		printf("%s\n", document.c_str() );
	}
	else{
		return false;
	}
}

bool HttpRequest::parse(){
	return true;
}
bool HttpRequest::parseOption(const string &key,const string &value){
	string *dest = nullptr;

	if( key == "host" )
		setHost( value );
	else if( key == "connection" )
		setConnection( value );
	else if( key == "accept" )
		setAccept( value );
	else if( key == "user-agent" )
		setUserAgent( value );
	else if( key == "accept-encoding" )
		setAcceptEncoding( value );
	else if( key == "accept-language" )
		setAcceptLanguage( value );
	else if( key == "content-type" )
		setContentType( value );
	else if( key == "content-length" ){
		unsigned long v;
		sscanf( value.c_str(), "%ul", &v);
		setContentLength( v );
	}
	else
		return false;

	return true;
}

const string &HttpRequest::getHeader(){
	return header;
}
void HttpRequest::setHeader(const string &_header){
	header = _header;
}

const string &HttpRequest::getDocument(){
	return document;
}
void HttpRequest::setDocument(const string &_document){
	document = _document;
}

HttpMethod HttpRequest::getHttpMethod(){
	return method;
}
void HttpRequest::setHttpMethod(HttpMethod _method){
	method = _method;
}

const string &HttpRequest::getHttpVersion(){
	return version;
}
void HttpRequest::setHttpVersion(const string &httpver){
	version = httpver;
}

Location &HttpRequest::getLocation(){
	return location;
}

const string &HttpRequest::getHost(){
	return host;
}
void HttpRequest::setHost(const string &_host){
	host = _host;
}

const string &HttpRequest::getConnection(){
	return connection;
}
void HttpRequest::setConnection(const string &_connection){
	connection = _connection;
}

const string &HttpRequest::getAccept(){
	return accept;
}
void HttpRequest::setAccept(const string &_accept){
	accept = _accept;
}

const string &HttpRequest::getUserAgent(){
	return userAgent;
}
void HttpRequest::setUserAgent(const string &_userAgent){
	userAgent = _userAgent;
}

const string &HttpRequest::getAcceptEncoding(){
	return acceptEncoding;
}
void HttpRequest::setAcceptEncoding(const string &_acceptEncoding){
	acceptEncoding = _acceptEncoding;
}

const string &HttpRequest::getAcceptLanguage(){
	return acceptLanguage;
}
void HttpRequest::setAcceptLanguage(const string &_acceptLanguage){
	acceptLanguage = _acceptLanguage;
}

void HttpRequest::setContentLength(unsigned long _contentLength){
	contentLength = _contentLength;
}

const string &HttpRequest::getContentType(){
	return contentType;
}
void HttpRequest::setContentType(const string &_contentType){
	contentType = _contentType;
}

unsigned long HttpRequest::getContentLength(){
	return document.length();
}