#include "JKReadWriteMutex.h"

USING_JK_NAMESPACE


ReadWriteMutex::ReadWriteMutex() 
	: _readCount(0) 
{
}

ReadWriteMutex::~ReadWriteMutex()
{
}

void ReadWriteMutex::readLock()
{
	std::unique_lock<std::mutex> lock(_readCountMutex);
	if (_readCount == 0)
	{
		_readWriteMutex.lock();
	}
	++_readCount;
}

void ReadWriteMutex::readUnlock()
{
	std::unique_lock<std::mutex> lock(_readCountMutex);
	if (_readCount > 0)
	{
		--_readCount;
		if (_readCount == 0)
		{
			_readWriteMutex.unlock();
		}
	}
}

void ReadWriteMutex::writeLock()
{
	_readWriteMutex.lock();
}

void ReadWriteMutex::writeUnlock()
{
	_readWriteMutex.unlock();
}
