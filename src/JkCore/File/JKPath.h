#pragma once

#include "Common/JKCommon.h"
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#if defined(_WIN32)
# include <windows.h>
#else
# include <unistd.h>
#endif
#include <sys/stat.h>


BEGIN_JK_NAMESPACE

class JK_API JKPath 
{
public:
	enum path_type {
		windows_path = 0,
		posix_path = 1,
#if defined(_WIN32)
		native_path = windows_path
#else
		native_path = posix_path
#endif
	};

	JKPath();
	JKPath(const JKPath &JKPath);
	JKPath(JKPath &&JKPath);
	JKPath(const char *string);
	JKPath(const std::string &string);

#if defined(_WIN32)
	JKPath(const std::wstring &wstring);
	JKPath(const wchar_t *wstring);
#endif

	size_t length() const;
	bool empty() const;
	bool is_absolute() const;
	JKPath make_absolute() const;

	bool exists() const;

	size_t file_size() const;

	bool is_directory() const;
	

	bool is_file() const;

	std::string extension() const;

	std::string filename() const;

	JKPath parent_path() const;

	JKPath operator/(const JKPath &other) const;

	std::string str(path_type type = native_path) const;
	void set(const std::string &str, path_type type = native_path);

	JKPath &operator=(const JKPath &JKPath);

	JKPath &operator=(JKPath &&JKPath);

	friend std::ostream &operator<<(std::ostream &os, const JKPath &path)
	{
		os << path.str();
		return os;
	}

	bool remove_file();

	bool resize_file(size_t target_length);

	static JKPath getcwd();

#if defined(_WIN32)
	std::wstring wstr(path_type type = native_path) const;


	void set(const std::wstring &wstring, path_type type = native_path);

	JKPath &operator=(const std::wstring &str);
#endif

	bool operator==(const JKPath &p) const;
	bool operator!=(const JKPath &p) const;

protected:
	static std::vector<std::string> tokenize(const std::string &string, const std::string &delim);
protected:
	path_type m_type;
	std::vector<std::string> m_path;
	bool m_absolute;
};

inline bool create_directory(const JKPath& p) {
#if defined(_WIN32)
	return CreateDirectoryW(p.wstr().c_str(), NULL) != 0;
#else
	return mkdir(p.str().c_str(), S_IRUSR | S_IWUSR | S_IXUSR) == 0;
#endif
}

END_JK_NAMESPACE
