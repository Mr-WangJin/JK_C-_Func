#pragma once

#include "Common/JKCommon.h"
#include "Common/JKBase.h"

BEGIN_JK_NAMESPACE

class JK_API JKDateUtil : public JKBase
{
public:
	JKDateUtil();
	~JKDateUtil();


private:
	time_t m_time;

};


END_JK_NAMESPACE