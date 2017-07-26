#pragma once

#include "JKFramework/SmartPtr/JKReferenced.h"

BEGIN_JK_NAMESPACE

class JK_API JKBase : public JKReferenced
{
public:
	JKBase() {};
	virtual ~JKBase() {};
};

END_JK_NAMESPACE