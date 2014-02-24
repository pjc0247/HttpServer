#include "stdafx.h"

#include "HttpServer.h"
#include "Monitor.h"

int main(int argc,char **argb){
	HttpServer *server = new HttpServer(9916);
	Monitor *monitor = new Monitor(*server);

	monitor->start();
	server->run();

	return 0;
}

