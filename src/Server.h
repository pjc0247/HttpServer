#ifndef _SERVER_H
#define _SERVER_H

#include <string>

#include "Config.h"
#include "ProcessPool.h"

struct ClientData{
	SOCKET socket;
	SOCKADDR_IN addr;
};

class Server{
public:
	Server(int port);
	Server(int nWorkers, int port);
	virtual ~Server();

	void getIOStatus(unsigned long *in,unsigned long *out);

	virtual void run();
	virtual void setopt(int level,int name,const char *value,int len);

protected:
	virtual bool onConnect(ClientData &client) = 0;

	virtual bool setup();
	virtual void cleanup();

	virtual int send(SOCKET sock,void *data,unsigned int length);
	virtual int recv(SOCKET sock,void *data,unsigned int length, bool complete=true);

	virtual void close(SOCKET sock);

	virtual void printError(const char *msg);

protected:
	SOCKET socket;
	SOCKADDR_IN addr;

	int port;

	ProcessPool<ClientData> workers;

	unsigned long totalIn, totalOut;
};


#endif //_SERVER_H