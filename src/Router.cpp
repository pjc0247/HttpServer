#include "stdafx.h"

#include "Router.h"
#include "Handler.h"

#include "HttpServer.h"

using namespace std;

Router::Router(){
}
Router::~Router(){
}

Router &Router::link(string &path, Router *router){
	return link( move(path), router );
}
Router &Router::link(string &&path, Router *router){
	assert( router != nullptr );
	assert( path.empty() == false );

	routes[ path ] = router;

	router->setParent( this );

	return *router;
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