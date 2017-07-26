#include "JKDateUtil.h"


USING_JK_NAMESPACE

JKDateUtil::JKDateUtil(const JKString &timeStr)
{
	tm tm_;
	int year, month, day, hour, minute, second;
	sscanf(timeStr.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	tm_.tm_year = year - 1900;
	tm_.tm_mon = month - 1;
	tm_.tm_mday = day;
	tm_.tm_hour = hour;
	tm_.tm_min = minute;
	tm_.tm_sec = second;
	tm_.tm_isdst = 0;

	m_time = mktime(&tm_);
}

JKDateUtil::~JKDateUtil()
{
}

JKString JKDateUtil::toString()
{
	char buf[128] = {0};
	tm* local; //本地时间   
	local = localtime(&m_time); //转为本地时间  
	strftime(buf, 64, "%Y-%m-%d %H:%M:%S", local);
	
	return JKString(buf);

// 	gmt = gmtime(&t);//转为格林威治时间  
// 	strftime(buf, 64, "%Y-%m-%d %H:%M:%S", gmt);
// 	std::cout << buf << std::endl;
}
