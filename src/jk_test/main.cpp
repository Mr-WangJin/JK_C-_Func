
#include "jk_file.h"
#include "jk_test_file.h"
#include "jk_test_win_thread.h"
#include <stdlib.h>

//extern bool ReadFile(const char* fileName, const char *_Mode, char *&buffer, long &lSize);

#include <iostream>



int main()
{

	JK_Test_File testFile;
	testFile.TestClass();

	system("pause");
	return 1;
}