#include "stdafx.h"
#include "Monitor.h"

#include "Server.h"

#include <functional>

using namespace std;

Monitor::Monitor(Server &_target) :
	target(_target){	

	activated = false;
}
Monitor::~Monitor(){
}

void Monitor::start(){
	activated = true;

	thread = ::thread(
		bind( &Monitor::monitor, this ) );
}
void Monitor::stop(){
	activated = false;

	thread.detach();
}

void Monitor::monitor(){
	if( !activated ) return;

	while( true ){
		/*
			
		*/
		unsigned long in,out;

		target.getIOStatus(&in,&out);

		printf("in : %5d / out : %5d\n",
			in, out);

		this_thread::sleep_for(
			chrono::milliseconds(1000) );
	}
}