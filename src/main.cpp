#include "stdafx.h"

#include "HttpServer.h"
#include "Monitor.h"

#include "URL.h"
#include "Location.h"

int main(int argc,char **argb){
	/*HttpServer *server = new HttpServer(9916);
	Monitor *monitor = new Monitor(*server);

	auto url = new URL("http://www.naver.com/");

	monitor->start();
	server->run();
	*/

	auto loc = new Location("main/main2/index.php?a=2");

	return 0;
}

