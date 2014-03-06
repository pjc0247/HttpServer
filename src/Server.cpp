#include "stdafx.h"
#include "Server.h"

#include "Config.h"

using namespace std;

Server::Server(int port){
	int nWorkers;

	nWorkers = std::thread::hardware_concurrency() * 2 - 1;

	this->Server::Server( nWorkers, port );
}
Server::Server(int nWorkers, int _port) :
	workers(nWorkers, bind(&Server::onConnect, this, placeholders::_1) ){

	socket = 0;
	totalIn = totalOut = 0;

	port = _port;
}
Server::~Server(){
}

void Server::printError(const char *msg){
	printf("%s\n", msg);
}

int Server::send(SOCKET sock,void *data,unsigned int length){
	int sent = ::send(sock, (const char *)data, length, 0);

	totalOut += sent;
	
	return sent;
}
int Server::recv(SOCKET sock,void *data,unsigned int length, bool complete){
	int received = 0;

	if( complete ){
		while( received != length ){
			received += 
				::recv(sock, (char*)data+received, length-received, 0);
		}
	}
	else {
		received = ::recv(sock, (char*)data, length, 0);
	}

	totalIn += received;

	return received;
}
void Server::close(SOCKET socket){

#ifdef TARGET_WIN32
	::closesocket( socket );
#else
	::close( socket );
#endif
}

void Server::getIOStatus(unsigned long *in,unsigned long *out){
	if( in != nullptr ) *in = totalIn;
	if( out != nullptr ) *out = totalOut;
}
void Server::setopt(int level,int name,const char *value,int len){
	setsockopt( socket, level, name, value, len);
}

bool Server::setup(){

#ifdef TARGET_WIN32
	WSAData wsa;
	WSAStartup(WS_VERSION, &wsa);
#endif

	socket = ::socket(PF_INET, SOCK_STREAM, 0);   
	if( socket == 0 ){
		printError("socket error");
		return false;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	addr.sin_port=htons(port);

	int optval = 1;
    setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));


	/* bind */
	if( ::bind(socket, (SOCKADDR*)&addr, sizeof(addr)) == -1 ){
		printError("bind error");
		return false;
	}

	/* listen */
	if( ::listen(socket, 5) == -1 ){
		printError("listen error");
		return false;
	}

	return true;
}
void Server::cleanup(){
	close( socket );

#ifdef TARGET_WIN32
	WSACleanup();
#endif
}

void Server::run(){
	if( !setup() ){
		printError("setup failed");
		return;
	}
	
	while( true ){
		SOCKADDR_IN clientAddr;
		SOCKET client;

#ifdef TARGET_WIN32
		int clientAddrSize;
#elif defined(TARGET_BSD)
		socklen_t clientAddrSize;
#endif

		clientAddrSize = sizeof(clientAddr);

		/* accept */
		client = ::accept(socket, (SOCKADDR*)&clientAddr, &clientAddrSize);

		if( client == 0 )
			printError("accept error");

		/*
		auto &thread = std::thread( [&](){
			onConnect(client, clientAddr);
		});*/
		ClientData cdata = 
			{client, clientAddr};
		workers.enqueue( cdata );
	}
}