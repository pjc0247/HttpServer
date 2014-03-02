#ifndef _LOCATION_H
#define _LOCATION_H

#include <string>
#include <vector>    
#include <unordered_map>
#include <forward_list>

typedef std::vector<std::string>::const_iterator LocationIterator;

class Location{
public:
	Location();
	Location(const std::string &requestURI);
	virtual ~Location();

	const std::string &getParameter(const std::string &key);
	const std::string &getLocation();

	const LocationIterator getIterator();
	const LocationIterator getEnd();

	// inlining
	const LocationIterator cbegin(){
		return getIterator();
	};
	const LocationIterator cend(){
		return getEnd();
	}
	

protected:
	bool parseQueryString(const std::string &query);
	bool parse();

	void setParameter(
		const std::string &key,const std::string &value);
	void setLocation(
		const std::string &location);

protected:
	std::string requestURI;

	std::vector<std::string> location;
	std::unordered_map<std::string,std::string> parameters;
};

#endif //_LOCATION_H