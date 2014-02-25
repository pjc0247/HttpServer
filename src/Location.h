#ifndef _LOCATION_H
#define _LOCATION_H

#include <string>
#include <vector>    
#include <unordered_map>

class Location{
public:
	Location();
	Location(const std::string &requestURI);
	virtual ~Location();

protected:
	bool parseQueryString(const std::string &query);
	bool parse();

protected:
	std::string requestURI;

	std::vector<std::string> location;
	std::unordered_map<std::string,std::string> parameters;
};

#endif //_LOCATION_H