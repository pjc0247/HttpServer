#include "stdafx.h"

#include "HttpRequest.h"

#include "Location.h"

HttpRequest::HttpRequest(){
	location = nullptr;
}
HttpRequest::~HttpRequest(){
	if( location != nullptr )
		delete location;
}