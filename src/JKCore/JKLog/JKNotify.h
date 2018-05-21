#pragma once

/** 
 *	日志记录文件，可设置通知级别
 */

#include "JKCommon/JKCommon.h"
#include "JKFramework/SmartPtr/JKReferenced.h"
#include <ostream>

BEGIN_JK_NAMESPACE

/** 通知级别 */
enum NotifySeverity {
		ALWAYS = 0,
		FATAL = 1,
		WARN = 2,
		NOTICE = 3,
		INFO = 4,
		DEBUG_INFO = 5,
		DEBUG_FP = 6
};

/** 设置通知级别 */
extern JK_API void setNotifyLevel(NotifySeverity severity);

/** 获取通知级别 */
extern JK_API NotifySeverity getNotifyLevel();

/** 初始化通知级别 */
extern JK_API bool initNotifyLevel();

#ifdef JK_NOTIFY_DISABLED
inline bool isNotifyEnabled(NotifySeverity) { return false; }
#else

/** 判断通知级别是否可用 */
extern JK_API bool isNotifyEnabled(NotifySeverity severity);
#endif

extern JK_API std::ostream& notify(const NotifySeverity severity);

inline std::ostream& notify(void) { return notify(JK_NAMESPACE::INFO); }

#define JK_NOTIFY(level) if (JK_NAMESPACE::isNotifyEnabled(level)) JK_NAMESPACE::notify(level)
#define JK_ALWAYS JK_NOTIFY(JK_NAMESPACE::ALWAYS)
#define JK_FATAL JK_NOTIFY(JK_NAMESPACE::FATAL)
#define JK_WARN JK_NOTIFY(JK_NAMESPACE::WARN)
#define JK_NOTICE JK_NOTIFY(JK_NAMESPACE::NOTICE)
#define JK_INFO JK_NOTIFY(JK_NAMESPACE::INFO)
#define JK_DEBUG JK_NOTIFY(JK_NAMESPACE::DEBUG_INFO)
#define JK_DEBUG_FP JK_NOTIFY(JK_NAMESPACE::DEBUG_FP)

class JK_API JKNotifyHandler : public JK_NAMESPACE::JKReferenced
{
public:
	virtual void notify(JK_NAMESPACE::NotifySeverity severity, const char *message) = 0;
};

extern JK_API void setNotifyHandler(JKNotifyHandler *handler);

extern JK_API JKNotifyHandler *getNotifyHandler();

/** 标准通知句柄类 */
class JK_API StandardNotifyHandler : public JKNotifyHandler
{
public:
	StandardNotifyHandler();

	void notify(JK_NAMESPACE::NotifySeverity severity, const char *message);
};

#if defined(WIN32) && !defined(__CYGWIN__)

	class JK_API WinDebugNotifyHandler : public JKNotifyHandler
	{
	public:
		void notify(JK_NAMESPACE::NotifySeverity severity, const char *message);
	};

#endif


END_JK_NAMESPACE

