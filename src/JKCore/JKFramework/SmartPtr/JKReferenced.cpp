#include "JKReferenced.h"
#include "JKObserver.h"
#include "JKDeleteHandler.h"
#include <stdlib.h>
#include <typeinfo>
#include <memory>
#include <set>

BEGIN_JK_NAMESPACE

template<typename T>
struct ResetPointer
{
	ResetPointer() :
		_ptr(0) {}

	ResetPointer(T* ptr) :
		_ptr(ptr) {}

	~ResetPointer()
	{
		delete _ptr;
		_ptr = 0;
	}

	inline ResetPointer& operator = (T* ptr)
	{
		if (_ptr == ptr) return *this;
		delete _ptr;
		_ptr = ptr;
		return *this;
	}

	void reset(T* ptr)
	{
		if (_ptr == ptr) return;
		delete _ptr;
		_ptr = ptr;
	}

	inline T& operator*() { return *_ptr; }

	inline const T& operator*() const { return *_ptr; }

	inline T* operator->() { return _ptr; }

	inline const T* operator->() const { return _ptr; }

	T* get() { return _ptr; }

	const T* get() const { return _ptr; }

	T* _ptr;
};

typedef ResetPointer<JKDeleteHandler> DeleteHandlerPointer;
typedef ResetPointer<std::mutex> GlobalMutexPointer;


#if !defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
static bool s_useThreadSafeReferenceCounting = getenv("OSG_THREAD_SAFE_REF_UNREF") != 0;
#endif


JKReferenced::JKReferenced() :
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	_observerSet(0),
	_refCount(0)
#else
	_refMutex(0),
	_refCount(0),
	_observerSet(0)
#endif
{
#if !defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
#ifndef ENFORCE_THREADSAFE
	if (s_useThreadSafeReferenceCounting)
#endif
		_refMutex = new std::mutex;
#endif

}

JKReferenced::JKReferenced(bool threadSafeRefUnref) :
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	_observerSet(0),
	_refCount(0)
#else
	_refMutex(0),
	_refCount(0),
	_observerSet(0)
#endif
{
#if !defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
#ifndef ENFORCE_THREADSAFE
	if (threadSafeRefUnref)
#endif
		_refMutex = new std::mutex;
#endif
}

JKReferenced::JKReferenced(const JKReferenced &) :
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	_observerSet(0),
	_refCount(0)
#else
	_refMutex(0),
	_refCount(0),
	_observerSet(0)
#endif
{
#if !defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
#ifndef ENFORCE_THREADSAFE
	if (s_useThreadSafeReferenceCounting)
#endif
		_refMutex = new std::mutex;
#endif
}
JKReferenced::~JKReferenced()
{
	// 	if (_refCount > 0)
	// 	{
	// 		OSG_WARN << "Warning: deleting still referenced object " << this << " of type '" << typeid(this).name() << "'" << std::endl;
	// 		OSG_WARN << "         the final reference count was " << _refCount << ", memory corruption possible." << std::endl;
	// 	}

	// signal observers that we are being deleted.
	signalObserversAndDelete(true, false);

	// delete the JKObserverSet
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	if (_observerSet.get()) static_cast<JKObserverSet*>(_observerSet.get())->unref();
#else
	if (_observerSet) static_cast<JKObserverSet*>(_observerSet)->unref();
#endif

#if !defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	if (_refMutex) delete _refMutex;
#endif
}

std::mutex* JKReferenced::getGlobalReferencedMutex()
{
	static GlobalMutexPointer s_ReferencedGlobalMutext = new std::mutex;
	return s_ReferencedGlobalMutext.get();
}

// helper class for forcing the global mutex to be constructed when the library is loaded.
struct InitGlobalMutexes
{
	InitGlobalMutexes()
	{
		JKReferenced::getGlobalReferencedMutex();
	}
};
static InitGlobalMutexes s_initGlobalMutexes;


// static std::auto_ptr<JKDeleteHandler> s_deleteHandler(0);
static DeleteHandlerPointer s_deleteHandler(0);

//static ApplicationUsageProxy Referenced_e0(ApplicationUsage::ENVIRONMENTAL_VARIABLE, "OSG_THREAD_SAFE_REF_UNREF", "");

void JKReferenced::setThreadSafeReferenceCounting(bool enableThreadSafeReferenceCounting)
{
#if !defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	s_useThreadSafeReferenceCounting = enableThreadSafeReferenceCounting;
#endif
}

bool JKReferenced::getThreadSafeReferenceCounting()
{
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	return true;
#else
	return s_useThreadSafeReferenceCounting;
#endif
}

void JKReferenced::setDeleteHandler(JKDeleteHandler* handler)
{
	s_deleteHandler.reset(handler);
}

JKDeleteHandler* JKReferenced::getDeleteHandler()
{
	return s_deleteHandler.get();
}

JKObserverSet* JKReferenced::getOrCreateObserverSet() const
{
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	JKObserverSet* observerSet = static_cast<JKObserverSet*>(_observerSet.get());
	while (0 == observerSet)
	{
		JKObserverSet* newObserverSet = new JKObserverSet(this);
		newObserverSet->ref();

		if (!_observerSet.assign(newObserverSet, 0))
		{
			newObserverSet->unref();
		}

		observerSet = static_cast<JKObserverSet*>(_observerSet.get());
	}
	return observerSet;
#else
	if (_refMutex)
	{
		std::unique_lock<std::mutex> lock(*_refMutex);
		if (!_observerSet)
		{
			_observerSet = new JKObserverSet(this);
			static_cast<JKObserverSet*>(_observerSet)->ref();
		}
		return static_cast<JKObserverSet*>(_observerSet);
	}
	else
	{
		if (!_observerSet)
		{
			_observerSet = new JKObserverSet(this);
			static_cast<JKObserverSet*>(_observerSet)->ref();
		}
		return static_cast<JKObserverSet*>(_observerSet);
	}
#endif
}

void JKReferenced::addObserver(JKObserver* observer) const
{
	getOrCreateObserverSet()->addObserver(observer);
}

void JKReferenced::removeObserver(JKObserver* observer) const
{
	getOrCreateObserverSet()->removeObserver(observer);
}

void JKReferenced::signalObserversAndDelete(bool signalDelete, bool doDelete) const
{
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	JKObserverSet* observerSet = static_cast<JKObserverSet*>(_observerSet.get());
#else
	JKObserverSet* observerSet = static_cast<JKObserverSet*>(_observerSet);
#endif

	if (observerSet && signalDelete)
	{
		observerSet->signalObjectDeleted(const_cast<JKReferenced*>(this));
	}

	if (doDelete)
	{
		if (getDeleteHandler()) deleteUsingDeleteHandler();
		else delete this;
	}
}

void JKReferenced::setThreadSafeRefUnref(bool threadSafe)
	{
#if !defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
		if (threadSafe)
		{
			if (!_refMutex)
			{
				// we want thread safe ref()/unref() so assign a mutex
				_refMutex = new std::mutex;
			}
		}
		else
		{
			if (_refMutex)
			{
				// we don't want thread safe ref()/unref() so remove any assigned mutex
				std::mutex* tmpMutexPtr = _refMutex;
				_refMutex = 0;
				delete tmpMutexPtr;
			}
		}
#endif
	}

int JKReferenced::unref_nodelete() const
{
#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
	return --_refCount;
#else
	if (_refMutex)
	{
		std::unique_lock<std::mutex> lock(*_refMutex);
		return --_refCount;
	}
	else
	{
		return --_refCount;
	}
#endif
}

void JKReferenced::deleteUsingDeleteHandler() const
{
	getDeleteHandler()->requestDelete(this);
}


END_JK_NAMESPACE