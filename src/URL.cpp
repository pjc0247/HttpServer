#include "stdafx.h"
#include "URL.h"

#include <regex>

using namespace std;

URL::URL() :
	url("") {
}
URL::URL(const string &url) :
	url(url) {

	parse();
}
URL::~URL(){

}

bool URL::parse(){
	regex expr("^((http|https):\\/\\/)?([^\\/]*)\\/\\S*");
	smatch match;

	regex_match( url, match, expr );

	protocol = match[2].str();
	domain = match[3].str();

	return true;
}

string &URL::getDomain(){
	return domain;
}
string &URL::getProtocol(){
	return protocol;
}
string &URL::getString(){
	return url;
}