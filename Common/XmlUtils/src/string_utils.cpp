﻿/*=========================================================================
  *
  * Program:      Sen2agri-Processors
  * Language:     C++
  * Copyright:    2015-2016, CS Romania, office@c-s.ro
  * See COPYRIGHT file for details.
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.

 =========================================================================*/
 
#include <limits>
#include <sstream>

#include <otbMacro.h>

#include "string_utils.hpp"

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> result;

    std::istringstream is(s);
    std::string item;
    while (std::getline(is, item, delim)) {
        result.emplace_back(std::move(item));
    }

    return result;
}

double ReadDouble(const std::string &s)
{
    try {
        if (s.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        return std::stod(s);
    } catch (const std::exception &e) {
        otbMsgDevMacro("Invalid double value " << s << ": " << e.what());

        return std::numeric_limits<double>::quiet_NaN();
    }
}

#if defined(WIN32) || defined(_WIN32) || defined(_WINDOWS)

void _wstrToUtf8__(std::string& dest, const std::wstring& input) {
    dest.clear();
    for (size_t i = 0; i < input.size(); i++) {
        wchar_t w = input[i];
        if (w <= 0x7f)
            dest.push_back((char)w);
        else if (w <= 0x7ff) {
            dest.push_back(0xc0 | ((w >> 6) & 0x1f));
            dest.push_back(0x80 | (w & 0x3f));
        }
        else if (w <= 0xffff) {
            dest.push_back(0xe0 | ((w >> 12) & 0x0f));
            dest.push_back(0x80 | ((w >> 6) & 0x3f));
            dest.push_back(0x80 | (w & 0x3f));
        }
        else if (w <= 0x10ffff) {
            dest.push_back(0xf0 | ((w >> 18) & 0x07));
            dest.push_back(0x80 | ((w >> 12) & 0x3f));
            dest.push_back(0x80 | ((w >> 6) & 0x3f));
            dest.push_back(0x80 | (w & 0x3f));
        }
        else
            dest.push_back('?');
    }
}

std::string _wstrToUtf8__(const std::wstring& str) {
    std::string result;
    _wstrToUtf8__(result, str);
    return result;
}

void _utf8toWStr__(std::wstring& dest, const std::string& input) {
    dest.clear();
    wchar_t w = 0;
    int bytes = 0;
    wchar_t err = L'�';

    for (size_t i = 0; i < input.size(); i++) {
        unsigned char c = (unsigned char)input[i];
        if (c <= 0x7f) {//first char
            if (bytes) {
                dest.push_back(err);
                bytes = 0;
            }
            dest.push_back((wchar_t)c);
        }
        else if (c <= 0xbf) {//second/third/etc bytes
            if (bytes) {
                w = ((w << 6) | (c & 0x3f));
                bytes--;
                if (bytes == 0)
                    dest.push_back(w);
            }
            else
                dest.push_back(err);
        }
        else if (c <= 0xdf) {//2byte sequence start
            bytes = 1;
            w = c & 0x1f;
        }
        else if (c <= 0xef) {//3byte sequence start
            bytes = 2;
            w = c & 0x0f;
        }
        else if (c <= 0xf7) {//3byte sequence start
            bytes = 3;
            w = c & 0x07;
        }
        else {
            dest.push_back(err);
            bytes = 0;
        }
    }
    if (bytes)
        dest.push_back(err);
}

std::wstring _utf8toWStr__(const std::string& str) {
    std::wstring result;
    _utf8toWStr__(result, str);
    return result;
}

/*
char* strptime(const char* s,
    const char* f,
    struct tm* tm) {
    std::cout << f << " "<<s << std::endl;
    // Isn't the C++ standard lib nice? std::get_time is defined such that its
    // format parameters are the exact same as strptime. Of course, we have to
    // create a string stream first, and imbue it with the current C locale, and
    // we also have to make sure we return the right things if it fails, or
    // if it succeeds, but this is still far simpler an implementation than any
    // of the versions in any of the C standard libraries.
    std::istringstream input(s);
    input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
    input >> std::get_time(tm, f);
    if (input.fail()) {
        return nullptr;
    }
    return (char*)(s + input.tellg());
}
*/
#endif // WIN32

/*
std::string _RemovePath__(std::string strFileName)
{
    std::string strSeparator = (strFileName.find("\\") != std::string::npos) ? "\\" : "/";
    int n = strFileName.find_last_of(strSeparator);
    return  n != std::string::npos ? strFileName.substr(n + 1) : strFileName;
}

std::string	_GetPath__(std::string strFileName)
{
    std::string strSeparator = (strFileName.find("\\") != std::string::npos) ? "\\" : "/";
    int n = strFileName.find_last_of(strSeparator);
    return n != std::string::npos ? strFileName.substr(0, n + 1) : "";
}

std::string _RemoveExtension__(std::string strFileName)
{
    std::string strSeparator = (strFileName.find("\\") != std::string::npos) ? "\\" : "/";
    int n = strFileName.rfind(".");
    return (n > strFileName.rfind(strSeparator)) ? strFileName.substr(0, n) : strFileName;
}


bool _FileExists__(std::string strFileName)
{
#if defined(WIN32) || defined(_WIN32) || defined(_WINDOWS)
    std::wstring strFileNameW = _utf8toWStr__(strFileName);

    return !(GetFileAttributesW(strFileNameW.c_str()) == INVALID_FILE_ATTRIBUTES); //GetFileAttributes ->stat
#else
    if (FILE* fp = fopen(strFileName.c_str(), "r"))
    {
        fclose(fp);
        return true;
    }
    else if (DIR* psDIR = opendir(strFileName.c_str()))
    {
        closedir(psDIR);
        return true;
    }
    else return false;
#endif
}
*/