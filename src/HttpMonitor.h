#ifndef _HTTP_MONITOR_H
#define _HTTP_MONITOR_H

#include "Monitor.h"

class Httpserver;

class HttpMonitor : public Monitor{
public:
	HttpMonitor(HttpServer *target);
	virtual ~HttpMonitor();

protected:
	virtual void monitor();

protected:
	HttpServer *target;
};

#endif //_HTTP_MONITOR_H