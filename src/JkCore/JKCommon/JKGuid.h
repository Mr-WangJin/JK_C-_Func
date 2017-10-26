#pragma once

#include "JKCommon/JKCommon.h"
#include <guiddef.h>

BEGIN_JK_NAMESPACE

class JK_API JKGuid
{
public:
	static GUID CreateGuid();

	static JKString GuidToString(const GUID &guid);
};

	



END_JK_NAMESPACE