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

bool Router::route(HttpRequest &request){
	//std::string &path = request.location->

	//routes.find(

	return true;
}