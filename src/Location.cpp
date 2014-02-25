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

bool Location::parseQueryString(const string &_query){
	const regex expr("([^&]+)=([^&]+)");
	smatch match;

	std::string query = move( _query );

	for(auto &it=query.begin();it!=query.end();++it){
		if( *it == '?' ){
			query.erase( query.begin(), ++it );
			break;
		}
	}

	while( regex_search( query, match, expr ) ){
		string &key = match[1].str();
		string &value = match[2].str();
		
		parameters[ key ] = value;
		printf("%s / %s\n", key.c_str(), value.c_str());
		
		query = match.suffix().str();
	}

	return true;
}
bool Location::parse(){
	const regex expr("([^\\/]+)+");
	smatch match;

	std::string uri = move( requestURI );

	while( regex_search( uri, match, expr ) ){
		string &f = match[0].str();
		
		location.push_back( f );
		
		uri = match.suffix().str();
	}

	parseQueryString(
		*location.rbegin() );
	
	return true;
}