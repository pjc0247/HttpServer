#include "stdafx.h"
#include "Encoding.h"

#include <Windows.h>

using namespace std;

Encoding::Encoding(){
}
Encoding::~Encoding(){
}

utf8string Encoding::encodeUTF8(const string &str){
	utf8string encoded;

	int wstrlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(),str.length(), NULL,NULL);
	wchar_t *wstr = new wchar_t[wstrlen + 1];

	MultiByteToWideChar(CP_ACP, 0, str.c_str(),str.length(), wstr, wstrlen);

	int cstrlen = WideCharToMultiByte(CP_UTF8, 0, wstr,wstrlen, NULL,NULL, 0,0);
	char *cstr = new char[cstrlen + 1];

	WideCharToMultiByte(CP_UTF8, 0, wstr,wstrlen, cstr,cstrlen, 0,0);
	cstr[cstrlen] = '\0';

	encoded.assign( (unsigned char *)cstr );

	delete[] wstr;
	delete[] cstr;

	return encoded;
}
string Encoding::decodeUTF8(const utf8string &str){
	string decoded;

	int wstrlen = MultiByteToWideChar(CP_UTF8, 0, (char *)str.c_str(),str.length(), NULL,NULL);
	wchar_t *wstr = new wchar_t[wstrlen + 1];

	MultiByteToWideChar(CP_UTF8, 0, (char *)str.c_str(),str.length(), wstr, wstrlen);

	int cstrlen = WideCharToMultiByte(CP_ACP, 0, wstr,wstrlen, NULL,NULL, 0,0);
	char *cstr = new char[cstrlen + 1];

	WideCharToMultiByte(CP_ACP, 0, wstr,wstrlen, cstr,cstrlen, 0,0);
	cstr[cstrlen] = '\0';

	decoded.assign( cstr );

	delete[] wstr;
	delete[] cstr;

	return decoded;
}

string Encoding::encodeURL(const utf8string &str){
	string encoded;

    for(auto &it=str.begin();it!=str.end();++it) {
		if( isprint(*it) )
			encoded += *it;
		else{
			char tmp[40];
			sprintf(tmp, "%%%02X", *it);

			encoded += tmp;
         }
    }

	return encoded;
}
string Encoding::decodeURL(const string &str){
	string decoded;



	return "";
}