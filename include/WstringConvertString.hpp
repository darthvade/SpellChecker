#ifndef __WSTRINGCVTSTRING_H__
#define __WSTRINGCVTSTRING_H__

#include <string>
#include <cstdlib>
#include <clocale>

namespace Convert {

	inline std::wstring StringToWstring(const std::string str) {
		unsigned int len = str.size() * 2;
		setlocale(LC_CTYPE, "");
		wchar_t *p = new wchar_t[len];
		mbstowcs(p, str.c_str(), len);
		std::wstring res(p);
		delete[] p;
		return res;
	}
	
	
	inline std::string WstringToString(const std::wstring str) {
	    unsigned len = str.size() * 4;
	    setlocale(LC_CTYPE, "");
	    char *p = new char[len];
	    wcstombs(p,str.c_str(),len);
	    std::string str1(p);
	    delete[] p;
	    return str1;
	}

}
#endif
