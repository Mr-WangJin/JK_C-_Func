
#include "jk_test_file.h"
#include "jk_test_win_thread.h"
#include "jk_try_catch.h"
#include "JKThread/JKThreadPool.h"
#include <stdlib.h>
#include <iostream>
#include <JKFramework\JKJsonCPPHelper.h>
#include "JKUtil\JKUrl.h"
#include "jk_test_notify.h"
#include <JKUtil/JKStringUtil.h>

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

	JK_NAMESPACE::JKThreadPool t;

	t.enqueue(test1, 2);
	t.enqueue(test2, 2000);
	t.enqueue(test2, 4000);
}

#include <basetsd.h>

int main()
{
//     const auto & strings = JKStringUtil::to_string(1, "sdf", 33);
//     for each (auto var in strings)
//     {
//         std::cout << var;
//     }

//    JKStringUtil::testVariadicTemplate("aa", "bb", "cc");


	testThreadPool();
	testNotify();
	
	system("pause");
	return 1;
}