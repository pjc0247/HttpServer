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

	LocationIterator getIterator();
	LocationIterator getEnd();

	// inlining
	const LocationIterator cbegin(){
		return dirs.cbegin();
	};
	const LocationIterator cend(){
		return dirs.cend();
	}
	LocationIterator begin(){
		return dirs.begin();
	};
	LocationIterator end(){
		return dirs.cend();
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

	std::string location;
	std::string queryString;

	std::vector<std::string> dirs;
	std::unordered_map<std::string,std::string> parameters;
};

#endif //_LOCATION_H