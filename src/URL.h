#ifndef _URL_H
#define _URL_H

#include <string>

class URL{
public:
	URL();
	URL(const std::string &url);
	virtual ~URL();

	std::string &getDomain();
	std::string &getProtocol();

	std::string &getString();

protected:
	bool parse();

protected:
	std::string url;

	std::string protocol;
	std::string domain;
};

#endif //_URL_H