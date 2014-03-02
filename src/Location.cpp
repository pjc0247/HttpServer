#include "stdafx.h"
#include "Location.h"

#include <regex>

using namespace std;

Location::Location(){
	this->Location::Location("");
}
Location::Location(const string &_requestURI) :
	requestURI(_requestURI) {

	parse();
}
Location::~Location(){
}

void Location::setParameter(
	const string &key,const string &value){

	parameters[ key ] = value;
}
const string &Location::getParameter(const string &key){
	auto &it = parameters.find( key );

	if( it == parameters.end() )
		return string("");
	
	return parameters[ key ];
}
void Location::setLocation(const std::string &_location){
//	location = move( _location );
}
const std::string &Location::getLocation(){
	//return location;
	return requestURI;
}

const LocationIterator Location::getIterator(){
	return location.cbegin();
}
const LocationIterator Location::getEnd(){
	return location.cend();
}

bool Location::parseQueryString(const string &_query){
	const regex expr("([^&]+)=([^&]+)");
	smatch match;

	std::string query = _query;

	for(auto &it=query.begin();it!=query.end();++it){
		if( *it == '?' ){
			query.erase( query.begin(), ++it );
			break;
		}
	}

	while( regex_search( query, match, expr ) ){
		string &key = match[1].str();
		string &value = match[2].str();
		
		setParameter(key, value);
		
		query = match.suffix().str();
	}

	return true;
}
bool Location::parse(){
	const regex expr("([^\\/]+)+");
	smatch match;

	std::string uri = requestURI;

	while( regex_search( uri, match, expr ) ){
		string &f = match[0].str();
		
		location.push_back( f );

		uri = match.suffix().str();
	}

	if( !location.empty() ){
		parseQueryString(
			*(location.rbegin()) );
	}
	
	return true;
}