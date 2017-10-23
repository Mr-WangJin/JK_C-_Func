#pragma once

#include "JKCommon/JKCommon.h"

BEGIN_JK_NAMESPACE


class JK_API JKCommandBase
{
public:
	JKCommandBase( void );

	virtual ~JKCommandBase( void );

public:
	virtual bool execute( void );

	virtual bool reverse_execute( void );
};


END_JK_NAMESPACE