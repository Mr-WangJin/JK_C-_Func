#include "JKObserver.h"

USING_JK_NAMESPACE

JKObserver::JKObserver()
{
}

JKObserver::~JKObserver()
{
}

JKObserverSet::JKObserverSet(const JKReferenced* observedObject) :
	_observedObject(const_cast<JKReferenced*>(observedObject))
{
	//OSG_NOTICE<<"JKObserverSet::JKObserverSet() "<<this<<std::endl;
}

JKObserverSet::~JKObserverSet()
{
	//OSG_NOTICE<<"JKObserverSet::~JKObserverSet() "<<this<<", _observers.size()="<<_observers.size()<<std::endl;
}

void JKObserverSet::addObserver(JKObserver* observer)
{
	//OSG_NOTICE<<"JKObserverSet::addObserver("<<observer<<") "<<this<<std::endl;
	std::unique_lock<std::mutex> lock(_mutex);
	_observers.insert(observer);
}

void JKObserverSet::removeObserver(JKObserver* observer)
{
	//OSG_NOTICE<<"JKObserverSet::removeObserver("<<observer<<") "<<this<<std::endl;
	std::unique_lock<std::mutex> lock(_mutex);
	_observers.erase(observer);
}

JK_NAMESPACE::JKReferenced* JKObserverSet::addRefLock()
{
	std::unique_lock<std::mutex> lock(_mutex);

	if (!_observedObject) return 0;

	int refCount = _observedObject->ref();
	if (refCount == 1)
	{
		// The object is in the process of being deleted, but our
		// objectDeleted() method hasn't been run yet (and we're
		// blocking it -- and the final destruction -- with our lock).
		_observedObject->unref_nodelete();
		return 0;
	}

	return _observedObject;
}

void JKObserverSet::signalObjectDeleted(void* ptr)
{
	std::unique_lock<std::mutex> lock(_mutex);

	for (Observers::iterator itr = _observers.begin();
		itr != _observers.end();
		++itr)
	{
		(*itr)->objectDeleted(ptr);
	}
	_observers.clear();

	// reset the observed object so that we know that it's now detached.
	_observedObject = 0;
}
