#include "JKNotify.h"
#include "JKFramework/SmartPtr/JKRef_Ptr.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iostream>

#include <ctype.h>

#define JK_INIT_SINGLETON_PROXY(ProxyName, Func) static struct ProxyName{ ProxyName() { Func; } } s_##ProxyName;

BEGIN_JK_NAMESPACE

class NullStreamBuffer : public std::streambuf
{
private:
	std::streamsize xsputn(const std::streambuf::char_type * /*str*/, std::streamsize n)
	{
		return n;
	}
};

struct NullStream : public std::ostream
{
public:
	NullStream() :
		std::ostream(new NullStreamBuffer)
	{
		_buffer = dynamic_cast<NullStreamBuffer *>(rdbuf());
	}

	~NullStream()
	{
		rdbuf(0);
		delete _buffer;
	}

protected:
	NullStreamBuffer* _buffer;
};

/** Stream buffer calling notify handler when buffer is synchronized (usually on std::endl).
* Stream stores last notification severity to pass it to handler call.
*/
struct NotifyStreamBuffer : public std::stringbuf
{
	NotifyStreamBuffer() : _severity(JK_NAMESPACE::NOTICE)
	{
	}

	void setNotifyHandler(JK_NAMESPACE::JKNotifyHandler *handler) { _handler = handler; }
	JK_NAMESPACE::JKNotifyHandler *getNotifyHandler() const { return _handler.get(); }

	/** Sets severity for next call of notify handler */
	void setCurrentSeverity(JK_NAMESPACE::NotifySeverity severity)
	{
		if (_severity != severity)
		{
			sync();
			_severity = severity;
		}
	}

	JK_NAMESPACE::NotifySeverity getCurrentSeverity() const { return _severity; }

private:

	int sync()
	{
		sputc(0); // string termination
		if (_handler.valid())
			_handler->notify(_severity, pbase());
		pubseekpos(0, std::ios_base::out); // or str(std::string())
		return 0;
	}

	JK_NAMESPACE::JKRef_Ptr<JK_NAMESPACE::JKNotifyHandler> _handler;
	JK_NAMESPACE::NotifySeverity _severity;
};

struct NotifyStream : public std::ostream
{
public:
	NotifyStream() :
		std::ostream(new NotifyStreamBuffer)
	{
		_buffer = dynamic_cast<NotifyStreamBuffer *>(rdbuf());
	}

	void setCurrentSeverity(JK_NAMESPACE::NotifySeverity severity)
	{
		_buffer->setCurrentSeverity(severity);
	}

	JK_NAMESPACE::NotifySeverity getCurrentSeverity() const
	{
		return _buffer->getCurrentSeverity();
	}

	~NotifyStream()
	{
		rdbuf(0);
		delete _buffer;
	}

protected:
	NotifyStreamBuffer* _buffer;
};

END_JK_NAMESPACE

USING_JK_NAMESPACE

//static JK_NAMESPACE::ApplicationUsageProxy Notify_e0(JK_NAMESPACE::ApplicationUsage::ENVIRONMENTAL_VARIABLE, "OSG_NOTIFY_LEVEL <mode>", "FATAL | WARN | NOTICE | DEBUG_INFO | DEBUG_FP | DEBUG | INFO | ALWAYS");

struct NotifySingleton
{
	NotifySingleton()
	{
		// _notifyLevel
		// =============

		_notifyLevel = JK_NAMESPACE::NOTICE; // Default value

		char* OSGNOTIFYLEVEL = getenv("OSG_NOTIFY_LEVEL");
		if (!OSGNOTIFYLEVEL) OSGNOTIFYLEVEL = getenv("OSGNOTIFYLEVEL");
		if (OSGNOTIFYLEVEL)
		{

			std::string stringOSGNOTIFYLEVEL(OSGNOTIFYLEVEL);

			// Convert to upper case
			for (std::string::iterator i = stringOSGNOTIFYLEVEL.begin();
				i != stringOSGNOTIFYLEVEL.end();
				++i)
			{
				*i = toupper(*i);
			}

			if (stringOSGNOTIFYLEVEL.find("ALWAYS") != std::string::npos)          _notifyLevel = JK_NAMESPACE::ALWAYS;
			else if (stringOSGNOTIFYLEVEL.find("FATAL") != std::string::npos)      _notifyLevel = JK_NAMESPACE::FATAL;
			else if (stringOSGNOTIFYLEVEL.find("WARN") != std::string::npos)       _notifyLevel = JK_NAMESPACE::WARN;
			else if (stringOSGNOTIFYLEVEL.find("NOTICE") != std::string::npos)     _notifyLevel = JK_NAMESPACE::NOTICE;
			else if (stringOSGNOTIFYLEVEL.find("DEBUG_INFO") != std::string::npos) _notifyLevel = JK_NAMESPACE::DEBUG_INFO;
			else if (stringOSGNOTIFYLEVEL.find("DEBUG_FP") != std::string::npos)   _notifyLevel = JK_NAMESPACE::DEBUG_FP;
			else if (stringOSGNOTIFYLEVEL.find("DEBUG") != std::string::npos)      _notifyLevel = JK_NAMESPACE::DEBUG_INFO;
			else if (stringOSGNOTIFYLEVEL.find("INFO") != std::string::npos)       _notifyLevel = JK_NAMESPACE::INFO;
			else std::cout << "Warning: invalid OSG_NOTIFY_LEVEL set (" << stringOSGNOTIFYLEVEL << ")" << std::endl;

		}

		// Setup standard notify handler
		JK_NAMESPACE::NotifyStreamBuffer *buffer = dynamic_cast<JK_NAMESPACE::NotifyStreamBuffer *>(_notifyStream.rdbuf());
		if (buffer && !buffer->getNotifyHandler())
			buffer->setNotifyHandler(new StandardNotifyHandler);
	}

	JK_NAMESPACE::NotifySeverity _notifyLevel;
	JK_NAMESPACE::NullStream     _nullStream;
	JK_NAMESPACE::NotifyStream   _notifyStream;
};

static NotifySingleton& getNotifySingleton()
{
	static NotifySingleton s_NotifySingleton;
	return s_NotifySingleton;
}

bool JK_NAMESPACE::initNotifyLevel()
{
	getNotifySingleton();
	return true;
}

// Use a proxy to force the initialization of the NotifySingleton during static initialization
JK_INIT_SINGLETON_PROXY(NotifySingletonProxy, JK_NAMESPACE::initNotifyLevel())

void JK_NAMESPACE::setNotifyLevel(JK_NAMESPACE::NotifySeverity severity)
{
	getNotifySingleton()._notifyLevel = severity;
}

JK_NAMESPACE::NotifySeverity JK_NAMESPACE::getNotifyLevel()
{
	return getNotifySingleton()._notifyLevel;
}

void JK_NAMESPACE::setNotifyHandler(JK_NAMESPACE::JKNotifyHandler *handler)
{
	JK_NAMESPACE::NotifyStreamBuffer *buffer = static_cast<JK_NAMESPACE::NotifyStreamBuffer*>(getNotifySingleton()._notifyStream.rdbuf());
	if (buffer) buffer->setNotifyHandler(handler);
}

JK_NAMESPACE::JKNotifyHandler* JK_NAMESPACE::getNotifyHandler()
{
	JK_NAMESPACE::NotifyStreamBuffer *buffer = static_cast<JK_NAMESPACE::NotifyStreamBuffer *>(getNotifySingleton()._notifyStream.rdbuf());
	return buffer ? buffer->getNotifyHandler() : 0;
}


#ifndef OSG_NOTIFY_DISABLED
bool JK_NAMESPACE::isNotifyEnabled(JK_NAMESPACE::NotifySeverity severity)
{
	return severity <= getNotifySingleton()._notifyLevel;
}
#endif

std::ostream& JK_NAMESPACE::notify(const JK_NAMESPACE::NotifySeverity severity)
{
	if (JK_NAMESPACE::isNotifyEnabled(severity))
	{
		getNotifySingleton()._notifyStream.setCurrentSeverity(severity);
		return getNotifySingleton()._notifyStream;
	}
	return getNotifySingleton()._nullStream;
}

StandardNotifyHandler::StandardNotifyHandler()
	: JKNotifyHandler()
{
}

void JK_NAMESPACE::StandardNotifyHandler::notify(JK_NAMESPACE::NotifySeverity severity, const char *message)
{
	if (severity <= JK_NAMESPACE::WARN)
		fputs(message, stderr);
	else
		fputs(message, stdout);
}

#if defined(WIN32) && !defined(__CYGWIN__)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

void JK_NAMESPACE::WinDebugNotifyHandler::notify(JK_NAMESPACE::NotifySeverity severity, const char *message)
{
	OutputDebugStringA(message);
}

#endif
