#pragma once

#include "JKReferenced.h"
#include "JKCommon/JKCommon.h"

#include <mutex>
#include <set>


BEGIN_JK_NAMESPACE

class JK_API JKObserver
{
public:
	JKObserver();
	virtual ~JKObserver();

	virtual void objectDeleted(void*) {}

};

class JK_API JKObserverSet : public JKReferenced
{
public:

	JKObserverSet(const JKReferenced* observedObject);

	JKReferenced* getObserverdObject() { return _observedObject; }
	const JKReferenced* getObserverdObject() const { return _observedObject; }

	JKReferenced* addRefLock();

	inline std::mutex* getObserverSetMutex() const { return &_mutex; }

	void addObserver(JKObserver* observer);
	void removeObserver(JKObserver* observer);

	void signalObjectDeleted(void* ptr);

	typedef std::set<JKObserver*> Observers;
	Observers& getObservers() { return _observers; }
	const Observers& getObservers() const { return _observers; }

protected:

	JKObserverSet(const JKObserverSet& rhs) : JKReferenced(rhs) {}
	JKObserverSet& operator = (const JKObserverSet& /*rhs*/) { return *this; }
	virtual ~JKObserverSet();

	mutable std::mutex			     _mutex;
	JKReferenced*                    _observedObject;
	Observers                        _observers;
};


END_JK_NAMESPACE