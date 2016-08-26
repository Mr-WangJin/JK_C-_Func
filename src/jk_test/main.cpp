
#include "jk_file.h"
#include "jk_test_file.h"
#include "jk_test_win_thread.h"
#include <stdlib.h>

#include <iostream>


#define TEST_CLASS(tClass) tClass t; t.TestClass();


int main()
{
	TEST_CLASS(JK_Test_File);

	system("pause");
	return 1;
}