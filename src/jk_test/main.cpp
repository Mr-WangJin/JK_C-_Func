
#include "jk_test_file.h"
#include "jk_test_win_thread.h"
#include "jk_try_catch.h"
#include "JKThread/JKThreadPool.h"
#include <stdlib.h>
#include <iostream>
#include <JKFramework\JKJsonCPPHelper.h>

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

void testThreadPool() {

	//JK_NAMESPACE::JKThreadPool t;

	//t.enqueue(test1, 2);
	//t.enqueue(test2, 2000);
	//t.enqueue(test2, 4000);
}

#include <basetsd.h>



int main()
{

	INT64  bb = 5441947182064855102;
	UINT64  aa = bb;

	
	system("pause");
	return 1;
}