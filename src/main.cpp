#include "stdafx.h"
#include "HttpServer.h"


int main(int argc,char **argb){
	HttpServer *server = new HttpServer(9916);
	server->run();
	return 0;
}

