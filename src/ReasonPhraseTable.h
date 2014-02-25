#ifndef _REASON_PHRASE_TABLE_H
#define _REASON_PHRASE_TABLE_H

#include <map>

enum HttpResponseCode;

class ReasonPhraseTable{
public:
	static ReasonPhraseTable *getInstance();
	static void releaseInstance();

	static ReasonPhraseTable *instance;

public:
	std::string &getPhrase(HttpResponseCode status);

	static std::string novalue;

private:
	ReasonPhraseTable();
	virtual ~ReasonPhraseTable();

	void insert(HttpResponseCode status,const std::string &phrase);
	bool initialize();

protected:
	std::map<HttpResponseCode, std::string> table;
};


#endif //_REASON_PHARASE_TABLE_H