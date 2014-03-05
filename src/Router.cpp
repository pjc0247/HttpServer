#include "stdafx.h"

#include "Router.h"
#include "Handler.h"

#include "HttpServer.h"

using namespace std;

Router::Router(){
}
Router::~Router(){
}

void Router::link(string &path, Router *router){
	link( move(path), router );
}
void Router::link(string &&path, Router *router){
	routes[ path ] = router;
}

bool Router::route(LocationIterator &it,HttpRequest &request){
	auto &pair = routes.find(*it);

	if( pair == routes.end() )
		return false;

	pair->second->route(++it, request);

	return true;
}