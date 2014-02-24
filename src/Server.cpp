#include "stdafx.h"
#include "Server.h"

using namespace std;

Server::Server(int _port) :
	workers(3, bind(&Server::onConnect, this, placeholders::_1) ){

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

void Server::getIOStatus(unsigned long *in,unsigned long *out){
	if( in != nullptr ) *in = totalIn;
	if( out != nullptr ) *out = totalOut;
}

bool Server::setup(){
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	socket = ::socket(PF_INET, SOCK_STREAM, 0);   
	if(socket == INVALID_SOCKET){
		printError("socket error");
		return false;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	addr.sin_port=htons(port);

	/* bind */
	if(::bind(socket, (SOCKADDR*) &addr, sizeof(addr))==SOCKET_ERROR){
		printError("bind error");
		return false;
	}

	/* listen */
	if(listen(socket, 5)==SOCKET_ERROR){
		printError("listen error");
		return false;
	}

	return true;
}
void Server::cleanup(){
	WSACleanup();
}

void Server::run(){
	if( !setup() ){
		printError("setup failed");
		return;
	}
	
	while( true ){
		SOCKADDR_IN clientAddr;
		SOCKET client;
		int clientAddrSize;

		clientAddrSize = sizeof(clientAddr);

		/* accept */
		client = accept(socket, (SOCKADDR*)&clientAddr, &clientAddrSize);
		if(client==INVALID_SOCKET)
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