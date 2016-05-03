#ifndef __JK_ASSERT_HPP_INCLUDED__
#define __JK_ASSERT_HPP_INCLUDED__

#include <sstream> // ostringstream

#ifdef JK_THROW_EXCEPTION_ON_BUG
#include <exception>

namespace jk {
// This exception is thrown when the sanity checks defined below fail,
// and #ifdef JK_THROW_EXCEPTION_ON_BUG.
class ScppAssertFailedException : public std::exception {
 public:
	ScppAssertFailedException(const char* file_name,
							  unsigned line_number,
							  const char* message);
	
	virtual const char* what() const throw () { return what_.c_str(); }
							  
	virtual ~ScppAssertFailedException() throw () {}
 private:
  std::string what_;
};
} // namespace jk
#endif

void JK_AssertErrorHandler(const char* file_name,
							 unsigned line_number,
							 const char* message);

// Permanent sanity check macro.
#define JK_ASSERT(condition, msg)                 \
    if(!(condition)) {                              \
        std::ostringstream s;                       \
        s << msg;                                   \
        JK_AssertErrorHandler(                    \
            __FILE__, __LINE__, s.str().c_str() );  \
	}

#ifdef _DEBUG
#	define JK_TEST_ASSERT_ON
#endif

// Temporary (for testing only) sanity check macro
#ifdef JK_TEST_ASSERT_ON
#	define JK_TEST_ASSERT(condition,msg) JK_ASSERT(condition, msg)
#else
#	define JK_TEST_ASSERT(condition,msg) // do nothing
#endif

#endif // __JK_ASSERT_HPP_INCLUDED__
