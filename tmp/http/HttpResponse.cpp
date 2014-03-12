#include "stdafx.h"

#include "HttpResponse.h"

#include "ReasonPhraseTable.h"

using namespace std;

static const char DoubleCrLf[] = "\r\n\r\n";
static const char CrLf[] = "\r\n";

HttpResponse::HttpResponse(){
}
HttpResponse::~HttpResponse(){
}

bool HttpResponse::compile(){
	ReasonPhraseTable *ptable = ReasonPhraseTable::getInstance();

	header.clear();

	char status[8];
	sprintf(status, "%d", getStatusCode());

	/* HttpVer / StatusCode / ReasonPhrase */
	header += getHttpVersion() + " ";
	header += string(status) + " ";
	header += ptable->getPhrase( getStatusCode() ) + CrLf;


	/* Server */
	header += "Server:" + getServerName() + CrLf;


	/* Content-type */
	header += "Content-type:" + getContentType();

	/* Content-length */
	char contentLength[32];
	sprintf(contentLength, "%ul", getContentLength());
	header += "Content-length:" + string(contentLength) + CrLf;

	/* Connection */
	header += "Connection:" + getConnectionType() + CrLf;


	/* CrLf */
	header += CrLf;

	return true;
}

const string HttpResponse::getHeader(){
	return header;
}

HttpResponseCode HttpResponse::getStatusCode(){
	return status;
}
void HttpResponse::setStatusCode(HttpResponseCode _status){
	status = _status;
}

const string &HttpResponse::getHttpVersion(){
	return version;
}
void HttpResponse::setHttpVersion(const string &httpver){
	version = httpver;
}

const string &HttpResponse::getServerName(){
	return server;
}
void HttpResponse::setServerName(const string &_server){
	server = _server;
}

const string &HttpResponse::getConnectionType(){
	return connectionType;
}
void HttpResponse::setConnectionType(const string &_connectionType){
	connectionType = _connectionType;
}

const string &HttpResponse::getContentType(){
	return contentType;
}
void HttpResponse::setContentType(const string &_contentType){
	contentType = _contentType;
}

const string &HttpResponse::getDocument(){
	return document;
}
void HttpResponse::setDocument(const string &_document){
	document = _document;
}

unsigned long HttpResponse::getContentLength(){
	return document.length();
	//return contentLength;
}