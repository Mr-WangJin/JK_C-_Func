#ifndef _JK_TEST_FILE_H_
#define _JK_TEST_FILE_H_

#include "jk_test.h"

class JK_Test_File : public JK_Test
{
public:
	JK_Test_File();
	~JK_Test_File();

	virtual void TestClass();

protected:
	void testReadFile();
	void testWriteFile();

private:
	const char *m_pFileName;
	
};



#endif