#ifndef _CONFIG_BSD_H
#define _CONFIG_BSD_H

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

typedef unsigned int SOCKET;
typedef sockaddr_in SOCKADDR_IN;
typedef sockaddr SOCKADDR;

#endif //_CONFIG_BSD_H