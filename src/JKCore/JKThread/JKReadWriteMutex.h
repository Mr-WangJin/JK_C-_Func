#pragma once

#include "JKCommon/JKCommon.h"
#include <mutex>

BEGIN_JK_NAMESPACE

class ReadWriteMutex
{
public:
	ReadWriteMutex();
	virtual ~ReadWriteMutex();

	virtual void readLock();
	virtual void readUnlock();

	virtual void writeLock();
	virtual void writeUnlock();

protected:
	ReadWriteMutex(const ReadWriteMutex&) {}
	ReadWriteMutex& operator = (const ReadWriteMutex&) { return *(this); }

	std::mutex  _readWriteMutex;
	std::mutex   _readCountMutex;
	unsigned int    _readCount;
};

class ScopedReadLock
{
public:
	ScopedReadLock(ReadWriteMutex& mutex) :_mutex(mutex) { _mutex.readLock(); }
	~ScopedReadLock() { _mutex.readUnlock(); }

protected:
	ReadWriteMutex& _mutex;

	ScopedReadLock& operator = (const ScopedReadLock&) { return *this; }
};


class ScopedWriteLock
{
public:
	ScopedWriteLock(ReadWriteMutex& mutex) :_mutex(mutex) { _mutex.writeLock(); }
	~ScopedWriteLock() { _mutex.writeUnlock(); }

protected:
	ReadWriteMutex& _mutex;

	ScopedWriteLock& operator = (const ScopedWriteLock&) { return *this; }
};

END_JK_NAMESPACE


