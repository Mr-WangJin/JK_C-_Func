#pragma once

/** 
 *	嵌入式计数指针类，支持多线程，内嵌监听者模式。
 */

#include "JKCommon/JKCommon.h"
#include <mutex>          // std::mutex

BEGIN_JK_NAMESPACE

class JKDeleteHandler;
class JKObserver;
class JKObserverSet;

class JK_API JKReferenced
{
	friend class JKDeleteHandler;
public:
	JKReferenced();
	explicit JKReferenced(bool threadSafeRefUnref);
	JKReferenced(const JKReferenced&);

	inline JKReferenced& operator = (const JKReferenced&) { return *this; }

	virtual void setThreadSafeRefUnref(bool threadSafe);

#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
		bool getThreadSafeRefUnref() const { return true; }
#else
	bool getThreadSafeRefUnref() const { return _refMutex != 0; }
#endif

		/** Get the mutex used to ensure thread safety of ref()/unref(). */
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
		std::mutex getRefMutex() const { return getGlobalReferencedMutex(); }
#else
	std::mutex* getRefMutex() const { return _refMutex; }
#endif

	/** Get the optional global JKReferenced mutex, this can be shared between all osg::JKReferenced.*/
	static std::mutex* getGlobalReferencedMutex();

	inline int ref() const;

	inline int unref() const;

	int unref_nodelete() const;

	inline int referenceCount() const { return _refCount; }

	JKObserverSet* getObserverSet() const
	{
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
			return static_cast<JKObserverSet*>(_observerSet.get());
#else
			return static_cast<JKObserverSet*>(_observerSet);
#endif
	};

	JKObserverSet* getOrCreateObserverSet() const;

	void addObserver(JKObserver* observer) const;

	void removeObserver(JKObserver* observer) const;

public:

	static void setThreadSafeReferenceCounting(bool enableThreadSafeReferenceCounting);

	static bool getThreadSafeReferenceCounting();

	static void setDeleteHandler(JKDeleteHandler* handler);

	static JKDeleteHandler* getDeleteHandler();

protected:

	virtual ~JKReferenced();

	void signalObserversAndDelete(bool signalDelete, bool doDelete) const;

	void deleteUsingDeleteHandler() const;

#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
		mutable OpenThreads::AtomicPtr  _observerSet;

		mutable OpenThreads::Atomic     _refCount;
#else

	mutable std::mutex*     _refMutex;
	mutable int             _refCount;
	mutable void*           _observerSet;
#endif
};

inline int JKReferenced::ref() const
{
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	return ++_refCount;
#else
	if (_refMutex)
	{
		std::unique_lock<std::mutex> lock(*_refMutex);
		return ++_refCount;
	}
	else
	{
		return ++_refCount;
	}
#endif
}

inline int JKReferenced::unref() const
{
	int newRef;
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	newRef = --_refCount;
	bool needDelete = (newRef == 0);
#else
	bool needDelete = false;
	if (_refMutex)
	{
		std::unique_lock<std::mutex> lock(*_refMutex);
		newRef = --_refCount;
		needDelete = newRef == 0;
	}
	else
	{
		newRef = --_refCount;
		needDelete = newRef == 0;
	}
#endif

	if (needDelete)
	{
		signalObserversAndDelete(true, true);
	}
	return newRef;
}

inline void intrusive_ptr_add_ref(JKReferenced* p) { p->ref(); }
inline void intrusive_ptr_release(JKReferenced* p) { p->unref(); }

END_JK_NAMESPACE