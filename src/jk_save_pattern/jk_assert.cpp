#include "jk_assert.hpp"

#include <iostream>	// cerr, endl, flush
#include <stdlib.h>	// exit()


using namespace std;

#ifdef JK_THROW_EXCEPTION_ON_BUG
namespace jk {
	ScppAssertFailedException::ScppAssertFailedException(const char* file_name,
														 unsigned line_number,
														 const char* message) {
		ostringstream s;
		s << "JK assertion failed with message '" << message
		  << "' in file " << file_name << " #" << line_number;
		
		what_ = s.str();
	}
}
#endif

void JK_AssertErrorHandler(const char* file_name,
							 unsigned line_number,
							 const char* message) {
	// This is a good place to put your debug breakpoint:
	// You can also add writing of the same info into a log file if appropriate.
	
#ifdef JK_THROW_EXCEPTION_ON_BUG
	throw jk::ScppAssertFailedException(file_name, line_number, message);
#else
	cerr << message << " in file " << file_name << " #" << line_number << endl << flush;
	// Terminate application
	exit(1);
#endif
}
