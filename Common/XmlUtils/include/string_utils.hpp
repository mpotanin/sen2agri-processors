#include <string>
#include <vector>
#include <iomanip>


std::vector<std::string> split(const std::string &s, char delim);
double ReadDouble(const std::string &s);

#if defined(WIN32) || defined(_WIN32) || defined(_WINDOWS)
void _wstrToUtf8__(std::string& dest, const std::wstring& input);
std::string _wstrToUtf8__(const std::wstring& str);

void _utf8toWStr__(std::wstring& dest, const std::string& input);
std::wstring  _utf8toWStr__(const std::string& str);

//char* strptime(const char* s, const char* f, struct tm* tm);
#endif // WIN32

/*
std::string	_GetPath__(std::string strFileName);
std::string	_RemovePath__(std::string strFile);
std::string _RemoveExtension__(std::string strFile);

bool _FileExists__(std::string strFileName);
*/