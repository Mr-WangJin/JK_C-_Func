
#include "jk_test_file.h"
#include "jk_test_win_thread.h"
#include "jk_try_catch.h"
#include "JKThread/JKThreadPool.h"
#include <stdlib.h>
#include <iostream>
#include <JKFramework\JKJsonCPPHelper.h>
#include <json\value.h>

USING_JK_NAMESPACE
using namespace Json;

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


class A : public JKJsonCPPBase<Json::Value>
{
public:
	A() { aaa = 3; };

	virtual void ParseJson(Json::Value& val) {
		JsonCppParseToInt(val, aaa);

	};

private:
	int aaa;

};

#include<json\value.h>

int main()
{
// 	TEST_CLASS(JK_Test_File);
// 	TEST_CLASS(JK_TryCatch);

	JKString sss = "asdfasdf";

	Json::Value root;

	//JKJsonValue<Json::Value> jsonValue;

	//jsonValue.jsonValue["asdf"] = 2;
	JsonCppWriteValue(root, sss);

	A* a = new A;
	Json::Value b;
	b["aaa"] = 3;
	root["a"] = b;

	sss = "d";
	JsonCppParseToString(root, sss);

	//if (root.isMember("a")) a->ParseJson(root["a"]);
	JsonCppParseToClass(root, a);


	system("pause");
	return 1;
}