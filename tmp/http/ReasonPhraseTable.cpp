#include "stdafx.h"
#include "ReasonPhraseTable.h"

#include "HttpProtocol.h"

using namespace std;

string ReasonPhraseTable::novalue = "NoValue";

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
	insert( HttpResponseCode::StatusContinue, "Continue" );

	// 2xx
	insert( HttpResponseCode::StatusOk, "OK" );
	insert( HttpResponseCode::StatusAccepted, "Accepted" );
	insert( HttpResponseCode::StatusNonAuthorizedInformation, "Non-Authoritative Information" );
	insert( HttpResponseCode::StatusNoContent, "No Content" );
	insert( HttpResponseCode::StatusResetContent, "Reset Content" );
	insert( HttpResponseCode::StatusPartialContent, "Partial Content" );

	// 3xx
	insert( HttpResponseCode::StatusMultipleChoices, "Multiple Choices" );
	insert( HttpResponseCode::StatusMovedPermanetly, "Moved Permanently" );
	insert( HttpResponseCode::StatusFound, "Found" );
	insert( HttpResponseCode::StatusSeeOther, "See Other" );
	insert( HttpResponseCode::StatusNotModified, "Not Modified" );
	insert( HttpResponseCode::StatusUseProxy, "Use Proxy" );

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