#include "stdafx.h"
#include "ReasonPhraseTable.h"

#include "HttpProtocol.h"

using namespace std;

ReasonPhraseTable *ReasonPhraseTable::instance = nullptr;
string ReasonPhraseTable::novalue = "NoValue";

ReasonPhraseTable *ReasonPhraseTable::getInstance(){
	if( instance == nullptr ){
		instance = new ReasonPhraseTable();
	}
	return instance;
}
void ReasonPhraseTable::releaseInstance(){
	if( instance != nullptr ){
		delete instance;
		instance = nullptr;
	}
}

ReasonPhraseTable::ReasonPhraseTable(){
	initialize();
}
ReasonPhraseTable::~ReasonPhraseTable(){
}

void ReasonPhraseTable::insert(
	HttpResponseCode status, const string &phrase){

	table[ status ] = phrase;
}
bool ReasonPhraseTable::initialize(){
	// 1xx

	// 2xx
	insert( HttpResponseCode::StatusOk, "OK" );

	// 3xx

	// 4xx
	insert( HttpResponseCode::StatusBadRequest, "Bad Request" );
	insert( HttpResponseCode::StatusForbidden, "Forbidden" );
	insert( HttpResponseCode::StatusNotFound, "Not Found" );

	// 5xx


	return true;
}

string &ReasonPhraseTable::getPhrase(HttpResponseCode status){
	auto &it = table.find( status );

	if( it == table.end() )
		return ReasonPhraseTable::novalue;

	return it->second;
}