#if !defined(_JK_TRYCATCH_H)
#define _JK_TRYCATCH_H

#include "jk_test.h"
#include <exception>
#include <iostream>

class JK_TryCatch : public JK_Test
{
public:
	JK_TryCatch();
	~JK_TryCatch();

	JK_TryCatch* getValue(bool bReturnExcept);

	virtual void TestClass(){
		try
		{
			JK_TryCatch tc;
			tc.getValue(true);
		}
		catch (std::exception &e)
		{
			std::cerr<<e.what();
		}
	};

};

class JK_Null_Exception : public std::exception
{
public:
	JK_Null_Exception();
	~JK_Null_Exception();
};


#endif  //_JK_TRYCATCH_H
