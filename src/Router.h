#ifndef _ROUTER_H
#define _ROUTER_H

#include <unordered_map>
#include <functional>
#include <string>

#include "Handler.h"
#include "Location.h"

struct HttpRequest;
struct HttpResponse;

class Router{
public:
	Router();
	virtual ~Router();

	void link(std::string &path, Router *router);
	void link(std::string &&path, Router *router);

	virtual bool route(LocationIterator &it, HttpRequest &request);

	Router *getParent();

protected:
	void setParent(Router *parent);

protected:
	Router *parent;

	std::unordered_map<std::string,Router*> routes;
};

#endif