#ifndef _REASON_PHRASE_TABLE_H
#define _REASON_PHRASE_TABLE_H

#include <map>

#include "ThreadSafeSingleton.h"

enum HttpResponseCode;

class ReasonPhraseTable : public ThreadSafeSingleton<ReasonPhraseTable>{
private:
	friend ThreadSafeSingleton;

	ReasonPhraseTable();
	virtual ~ReasonPhraseTable();

public:
	std::string &getPhrase(HttpResponseCode status);

protected:
	void insert(HttpResponseCode status,const std::string &phrase);
	bool initialize();


public:
	static std::string novalue;

protected:
	std::map<HttpResponseCode, std::string> table;
};


#endif //_REASON_PHARASE_TABLE_H