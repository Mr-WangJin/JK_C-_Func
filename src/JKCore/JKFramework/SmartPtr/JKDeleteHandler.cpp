#include "JKDeleteHandler.h"
#include "JKReferenced.h"

USING_JK_NAMESPACE

JKDeleteHandler::JKDeleteHandler(int numberOfFramesToRetainObjects)
	: _numFramesToRetainObjects(numberOfFramesToRetainObjects)
	, _currentFrameNumber(0)
{
}

JKDeleteHandler::~JKDeleteHandler()
{
	// flushAll();
}

void JKDeleteHandler::flush()
{
	typedef std::list<const JKReferenced*> DeletionList;
	DeletionList deletionList;

	{
		// gather all the objects to delete whilst holding the mutex to the _objectsToDelete
		// list, but delete the objects outside this scoped lock so that if any objects deleted
		// unref their children then no deadlock happens.
		std::unique_lock<std::mutex> lock(_mutex);
		unsigned int frameNumberToClearTo = _currentFrameNumber - _numFramesToRetainObjects;

		ObjectsToDeleteList::iterator itr;
		for (itr = _objectsToDelete.begin();
			itr != _objectsToDelete.end();
			++itr)
		{
			if (itr->first > frameNumberToClearTo) break;

			deletionList.push_back(itr->second);

			itr->second = 0;
		}

		_objectsToDelete.erase(_objectsToDelete.begin(), itr);
	}

	for (DeletionList::iterator ditr = deletionList.begin();
		ditr != deletionList.end();
		++ditr)
	{
		doDelete(*ditr);
	}

}

void JKDeleteHandler::flushAll()
{
	unsigned int temp_numFramesToRetainObjects = _numFramesToRetainObjects;
	_numFramesToRetainObjects = 0;

	typedef std::list<const JKReferenced*> DeletionList;
	DeletionList deletionList;

	{
		// gather all the objects to delete whilst holding the mutex to the _objectsToDelete
		// list, but delete the objects outside this scoped lock so that if any objects deleted
		// unref their children then no deadlock happens.
		std::unique_lock<std::mutex> lock(_mutex);
		ObjectsToDeleteList::iterator itr;
		for (itr = _objectsToDelete.begin();
			itr != _objectsToDelete.end();
			++itr)
		{
			deletionList.push_back(itr->second);
			itr->second = 0;
		}

		_objectsToDelete.erase(_objectsToDelete.begin(), _objectsToDelete.end());
	}

	for (DeletionList::iterator ditr = deletionList.begin();
		ditr != deletionList.end();
		++ditr)
	{
		doDelete(*ditr);
	}

	_numFramesToRetainObjects = temp_numFramesToRetainObjects;
}

void JKDeleteHandler::requestDelete(const JKReferenced* object)
{
	if (_numFramesToRetainObjects == 0) doDelete(object);
	else
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_objectsToDelete.push_back(FrameNumberObjectPair(_currentFrameNumber, object));
	}
}

