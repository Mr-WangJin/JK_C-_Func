#include "jk_test_file.h"
#include "jk_file.h"
#include <stdlib.h>
#include <iostream>
#include "thread/jk_thread.h"

using namespace JK_NAMESPACE;

JK_Test_File::JK_Test_File()
{
	m_pFileName = "testfile";
}

JK_Test_File::~JK_Test_File()
{

}


void JK_Test_File::TestClass()
{
	COUT_STR("Start test file.....")
	this->testWriteFile();
	this->testReadFile();
	COUT_STR("End test file.....")
}

void JK_Test_File::testReadFile()
{
	/* test file */
	char *buffer = NULL;
	long bufSize = 0;

	if (JK_File::ReadFile(m_pFileName, "r", buffer, bufSize) == true)
		std::cout<<"Test Read File is TRUE!"<<std::endl;
	else
		std::cout<<"Test Read File if False!"<<std::endl;
	free(buffer);
}
void JK_Test_File::testWriteFile()
{
	/* test file */
	char *buffer = "testFile";
	long bufSize = 8;

	if (JK_File::WriteFile(m_pFileName, "w+", buffer, bufSize) == true)
		std::cout<<"Test Write File is TRUE!"<<std::endl;
	else
		std::cout<<"Test Write File if False!"<<std::endl;

}