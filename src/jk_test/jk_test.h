#ifndef _JK_TEST_
#define _JK_TEST_


#define COUT_STR(str)		std::cout<<str<<std::endl;


class JK_Test
{
public:
	virtual ~JK_Test(){};

	virtual void TestClass() = 0;
};


#endif