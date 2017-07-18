
#include "File/JKFile.h"
#include "jk_test_file.h"
#include "jk_test_win_thread.h"
#include "jk_try_catch.h"

#include <stdlib.h>
#include <iostream>

#include "jk_framework/jk_ioc.h"

using namespace JK_NAMESPACE;

#define TEST_CLASS(tClass)	\
	std::cout<<"-------------Begin Test "#tClass"------------------"<<std::endl;\
	tClass t##tClass; t##tClass.TestClass();



int main()
{
	TEST_CLASS(JK_Test_File);
	TEST_CLASS(JK_TryCatch);

	TempTest a;
	a.getValue<int>();


	system("pause");
	return 1;
}