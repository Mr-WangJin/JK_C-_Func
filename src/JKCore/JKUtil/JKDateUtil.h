#pragma once

#include "JKCommon/JKCommon.h"
#include "JKCommon/JKBase.h"

BEGIN_JK_NAMESPACE

class JK_API JKDateUtil : public JKBase
{
public:
	/** 
	 *	时间格式 yyyy-MM-dd hh:mm::ss
	 */
	JKDateUtil(const JKString &);
	~JKDateUtil();

	JKString utc_time();


private:
	time_t m_time;

};


END_JK_NAMESPACE