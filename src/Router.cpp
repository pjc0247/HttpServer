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
	assert(router != nullptr);

	routes[ path ] = router;

	router->setParent( this );
}

Router *Router::getParent(){
	return parent;
}
void Router::setParent(Router *_parent){
	parent = _parent;
}

bool Router::route(LocationIterator &it,HttpRequest &request){
	if( it == request.location->end() ){
		return false;
	}

	auto pair = routes.find(*it);

	if( pair == routes.end() ){
		return false;
	}

	pair->second->route(++it, request);

	return true;
}