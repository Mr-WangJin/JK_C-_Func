#include "JKPath.h"
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <cstring>

USING_JK_NAMESPACE


JKPath::JKPath() 
	: m_type(native_path)
	, m_absolute(false) 
{ }

JKPath::JKPath(const JKPath &path)
	: m_type(path.m_type)
	, m_path(path.m_path)
	, m_absolute(path.m_absolute)
{}

JKPath::JKPath(JKPath &&path)
	: m_type(path.m_type)
	, m_path(std::move(path.m_path))
	, m_absolute(path.m_absolute) 
{}

JKPath::JKPath(const char *string) 
{ 
	set(string);
}

JKPath::JKPath(const std::string &string) 
{ 
	set(string); 
}

#if defined(_WIN32)

JKPath::JKPath(const std::wstring &wstring) { set(wstring); }
JKPath::JKPath(const wchar_t *wstring) { set(wstring); }

#endif

size_t JKPath::length() const 
{ 
	return m_path.size(); 
}

bool JKPath::empty() const 
{ 
	return m_path.empty(); 
}

bool JKPath::is_absolute() const
{ 
	return m_absolute; 
}

JKPath JKPath::make_absolute() const 
{
#if !defined(_WIN32)
	char temp[PATH_MAX];
	if (realpath(str().c_str(), temp) == NULL)
		throw std::runtime_error("Internal error in realpath(): " + std::string(strerror(errno)));
	return JKPath(temp);
#else
	std::wstring value = wstr(), out(MAX_PATH, '\0');
	DWORD length = GetFullPathNameW(value.c_str(), MAX_PATH, &out[0], NULL);
	if (length == 0)
		throw std::runtime_error("Internal error in realpath(): " + std::to_string(GetLastError()));
	return JKPath(out.substr(0, length));
#endif
}

bool JKPath::exists() const 
{
#if defined(_WIN32)
	return GetFileAttributesW(wstr().c_str()) != INVALID_FILE_ATTRIBUTES;
#else
	struct stat sb;
	return stat(str().c_str(), &sb) == 0;
#endif

}

size_t JKPath::file_size() const 
{
#if defined(_WIN32)
	struct _stati64 sb;
	if (_wstati64(wstr().c_str(), &sb) != 0)
			throw std::runtime_error("path::file_size(): cannot stat file \"" + str() + "\"!");
#else
	struct stat sb;
	if (stat(str().c_str(), &sb) != 0)
		throw std::runtime_error("path::file_size(): cannot stat file \"" + str() + "\"!");
#endif
	return (size_t)sb.st_size;
}

bool JKPath::is_directory() const 
{
#if defined(_WIN32)
	DWORD result = GetFileAttributesW(wstr().c_str());
	if (result == INVALID_FILE_ATTRIBUTES)
		return false;
	return (result & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
	struct stat sb;
	if (stat(str().c_str(), &sb))
		return false;
	return S_ISDIR(sb.st_mode);
#endif
}

bool JKPath::is_file() const 
{
#if defined(_WIN32)
	DWORD attr = GetFileAttributesW(wstr().c_str());
	return (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY) == 0);
#else
	struct stat sb;
	if (stat(str().c_str(), &sb))
		return false;
	return S_ISREG(sb.st_mode);
#endif
}

std::string JKPath::extension() const
{
	const std::string &name = filename();
	size_t pos = name.find_last_of(".");
	if (pos == std::string::npos)
		return "";
	return name.substr(pos + 1);
}

std::string JKPath::filename() const 
{
	if (empty())
		return "";
	const std::string &last = m_path[m_path.size() - 1];
	return last;
}

JKPath JKPath::parent_path() const 
{
	JKPath result;
	result.m_absolute = m_absolute;

	if (m_path.empty()) {
		if (!m_absolute)
			result.m_path.push_back("..");
	}
	else {
		size_t until = m_path.size() - 1;
		for (size_t i = 0; i < until; ++i)
			result.m_path.push_back(m_path[i]);
	}
	return result;
}

JKPath JKPath::operator/(const JKPath &other) const 
{
	if (other.m_absolute)
		throw std::runtime_error("path::operator/(): expected a relative path!");
	if (m_type != other.m_type)
		throw std::runtime_error("path::operator/(): expected a path of the same type!");

	JKPath result(*this);

	for (size_t i = 0; i<other.m_path.size(); ++i)
		result.m_path.push_back(other.m_path[i]);

	return result;
}

std::string JKPath::str(PathType type /*= native_path*/) const
{
	std::ostringstream oss;

	if (m_type == posix_path && m_absolute)
		oss << "/";

	for (size_t i = 0; i<m_path.size(); ++i) {
		oss << m_path[i];
		if (i + 1 < m_path.size()) {
			if (type == posix_path)
				oss << '/';
			else
				oss << '\\';
		}
	}

	return oss.str();
}

void JKPath::set(const std::string &str, PathType type/* = native_path*/)
{
	m_type = type;
	if (type == windows_path) {
		m_path = tokenize(str, "/\\");
		m_absolute = str.size() >= 2 && std::isalpha(str[0]) && str[1] == ':';
	}
	else {
		m_path = tokenize(str, "/");
		m_absolute = !str.empty() && str[0] == '/';
	}
}

JKPath &JKPath::operator=(const JKPath &path)
{
	m_type = path.m_type;
	m_path = path.m_path;
	m_absolute = path.m_absolute;
	return *this;
}

JKPath &JKPath::operator=(JKPath &&path) 
{
	if (this != &path) {
		m_type = path.m_type;
		m_path = std::move(path.m_path);
		m_absolute = path.m_absolute;
	}
	return *this;
}


bool JKPath::remove_file() 
{
#if !defined(_WIN32)
	return std::remove(str().c_str()) == 0;
#else
	return DeleteFileW(wstr().c_str()) != 0;
#endif
}

bool JKPath::resize_file(size_t target_length) 
{
#if !defined(_WIN32)
	return ::truncate(str().c_str(), (off_t)target_length) == 0;
#else
	HANDLE handle = CreateFileW(wstr().c_str(), GENERIC_WRITE, 0, nullptr, 0, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (handle == INVALID_HANDLE_VALUE)
		return false;
	LARGE_INTEGER size;
	size.QuadPart = (LONGLONG)target_length;
	if (SetFilePointerEx(handle, size, NULL, FILE_BEGIN) == 0) {
		CloseHandle(handle);
		return false;
	}
	if (SetEndOfFile(handle) == 0) {
		CloseHandle(handle);
		return false;
	}
	CloseHandle(handle);
	return true;
#endif
}

JKPath JKPath::getcwd() 
{
#if !defined(_WIN32)
	char temp[PATH_MAX];
	if (::getcwd(temp, PATH_MAX) == NULL)
		throw std::runtime_error("Internal error in getcwd(): " + std::string(strerror(errno)));
	return JKPath(temp);
#else
	std::wstring temp(MAX_PATH, '\0');
	if (!_wgetcwd(&temp[0], MAX_PATH))
		throw std::runtime_error("Internal error in getcwd(): " + std::to_string(GetLastError()));
	return JKPath(temp.c_str());
#endif
	}

#if defined(_WIN32)
std::wstring JKPath::wstr(PathType type /*= native_path*/) const
{
	std::string temp = str(type);
	int size = MultiByteToWideChar(CP_UTF8, 0, &temp[0], (int)temp.size(), NULL, 0);
	std::wstring result(size, 0);
	MultiByteToWideChar(CP_UTF8, 0, &temp[0], (int)temp.size(), &result[0], size);
	return result;
}


void JKPath::set(const std::wstring &wstring, PathType type /*= native_path*/)
{
	std::string string;
	if (!wstring.empty()) {
		int size = WideCharToMultiByte(CP_UTF8, 0, &wstring[0], (int)wstring.size(),
			NULL, 0, NULL, NULL);
		string.resize(size, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstring[0], (int)wstring.size(),
			&string[0], size, NULL, NULL);
	}
	set(string, type);
}

JKPath &JKPath::operator=(const std::wstring &str) 
{ 
	set(str);
	return *this;
}
#endif

bool JKPath::operator==(const JKPath &p) const
{
	return p.m_path == m_path;
}

bool JKPath::operator!=(const JKPath &p) const 
{ 
	return p.m_path != m_path;
}

std::vector<std::string> JKPath::tokenize(const std::string &string, const std::string &delim) 
{
	std::string::size_type lastPos = 0, pos = string.find_first_of(delim, lastPos);
	std::vector<std::string> tokens;

	while (lastPos != std::string::npos) {
		if (pos != lastPos)
			tokens.push_back(string.substr(lastPos, pos - lastPos));
		lastPos = pos;
		if (lastPos == std::string::npos || lastPos + 1 == string.length())
			break;
		pos = string.find_first_of(delim, ++lastPos);
	}

	return tokens;
}