#include "stdafx.h"

#include <thread>

#include "HttpServer.h"
#include "HttpMonitor.h"

using namespace std;

HttpMonitor::HttpMonitor(HttpServer *_target) :
	target(_target) {

	activated = false;
}
HttpMonitor::~HttpMonitor(){

}

void HttpMonitor::monitor(){
	if( !activated ) return;

	unsigned int oldReqs = 0;

	while( true ){
		/*
			
		*/
		unsigned long in,out;
		unsigned int reqs = target->getRequestCount();

		target->getIOStatus(&in,&out);

		printf("[%s] in : %5d / out : %5d / Reqs : %5d/s\n",
			target->getServerName().c_str(),
			in, out,
			(reqs - oldReqs));

		oldReqs = reqs;

		this_thread::sleep_for(
			chrono::milliseconds(1000) );
	}
}