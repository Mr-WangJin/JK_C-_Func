#include "jk_try_catch.h"

JK_TryCatch::JK_TryCatch()
{

}
JK_TryCatch::~JK_TryCatch()
{

}

JK_TryCatch* JK_TryCatch::getValue(bool bReturnExcept)
{
	if (bReturnExcept)
	{
		throw JK_Null_Exception();
	}else
	{
		return this;
	}
}


JK_Null_Exception::JK_Null_Exception()
	: std::exception("Ptr is null!")
{

}
JK_Null_Exception::~JK_Null_Exception()
{

}