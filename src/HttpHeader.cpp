#include "stdafx.h"

#include "HttpHeader.h"

#include <regex>

using namespace std;

HttpHeader::HttpHeader(){
}
HttpHeader::HttpHeader(const string &header){
	load( header );
}
HttpHeader::~HttpHeader(){
}

const string &HttpHeader::getField(const string &name){
	data.get( name );
}
void HttpHeader::setField(const string &name, const string &value){
	data.set( name, value );
}

bool HttpHeader::load(const string &header){
	regex expr("([a-zA-Z_-]*)\\s?:\\s?(.*)");
	smatch match;

	string tmp = header;

	while( regex_search( tmp, match, expr ) ){
		string key = match[1].str();
		string value = match[2].str();

		transform( key.begin(),key.end(),key.begin(), ::tolower );
		
		data.set( key, value );

		tmp = match.suffix().str();
	}

	return true;
}
std::string HttpHeader::compile(){
	string header;

	for( auto &pair : data ){
		header += pair.first + ":" + pair.second;
		header += "\r\n";
	}
	header += "\r\n";

	return header;
}