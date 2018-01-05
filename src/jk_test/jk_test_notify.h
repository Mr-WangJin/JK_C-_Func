#pragma once


#include "JKLog/JKNotify.h"

USING_JK_NAMESPACE;

void testNotify()
{
	//initNotifyLevel()
	setNotifyLevel(DEBUG_FP);

	JK_DEBUG << "bbb" << std::endl;
	JK_FATAL << "aaa" << std::endl;
	//notify(INFO);

}
