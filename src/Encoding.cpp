#include "stdafx.h"
#include "Encoding.h"

using namespace std;

Encoding *Encoding::instance = nullptr;

Encoding *Encoding::getInstance(){
	if( instance == nullptr ){
		instance = new Encoding();
	}
	return instance;
}
void Encoding::releaseInstance(){
	if( instance != nullptr ){
		delete instance;
		instance = nullptr;
	}
}

Encoding::Encoding(){
}
Encoding::~Encoding(){
}

string Encoding::encodeURL(const string &str){
	return "";
}
string Encoding::decodeURL(const string &str){
	return "";
}