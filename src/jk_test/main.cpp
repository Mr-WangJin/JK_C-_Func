
#include "jk_test_file.h"
#include "jk_test_win_thread.h"
#include "jk_try_catch.h"
#include "JKThread/JKThreadPool.h"
#include <stdlib.h>
#include <iostream>

USING_JK_NAMESPACE

#define TEST_CLASS(tClass)	\
	std::cout<<"-------------Begin Test "#tClass"------------------"<<std::endl;\
	tClass t##tClass; t##tClass.TestClass();



int test1(int i) {
	for (int a = i; a < i + 1000; ++a)
	{
		std::cout << a << std::endl;
	}
	return 2;
};
int test2(int i) {
	for (int a = i; a< i+1000; ++a)
	{
		std::cout << a << std::endl;
	}
	return 2;
};


int main()
{
// 	TEST_CLASS(JK_Test_File);
// 	TEST_CLASS(JK_TryCatch);

	JK_NAMESPACE::JKThreadPool t;

	t.enqueue(test1, 2);
	t.enqueue(test2, 2000);
	t.enqueue(test2, 4000);


	system("pause");
	return 1;
}