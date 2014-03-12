#ifndef _MONITOR_H
#define _MONITOR_H

#include <thread>

class Server;

class Monitor{
public:
	Monitor(Server &target);
	virtual ~Monitor();

	void start();
	void stop();

protected:
	void monitor();

protected:
	Server &target;
	std::thread thread;

	bool activated;
};

#endif //_MONITOR_H