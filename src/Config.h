#ifndef _CONFIG_H
#define _CONFIG_H

#if defined(WIN32) || defined(_WIN32)
	#define TARGET_WIN32 1
#else
	#define TARGET_BSD 1
#endif

#if defined(TARGET_WIN32)
	#include "Config_win32.h"
#elif defined(TARGET_BSD)
	#include "Config_bsd.h"
#endif


#define BACKLOG_SIZE 5
#define INBUF_SIZE 64


#endif //_CONFIG_H