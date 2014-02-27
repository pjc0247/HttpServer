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

	const std::string &getParameter(const std::string &key);

protected:
	bool parseQueryString(const std::string &query);
	bool parse();

	void setParameter(
		const std::string &key,const std::string &value);

protected:
	std::string requestURI;

	std::vector<std::string> location;
	std::unordered_map<std::string,std::string> parameters;
};

#endif //_LOCATION_H