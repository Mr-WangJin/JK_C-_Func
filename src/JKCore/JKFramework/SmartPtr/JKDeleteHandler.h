#pragma once

/** 
 *	删除JKReferenced对象 默认句柄类， 支持多线程
 */

#include "JKCommon/JKCommon.h"
#include <list>
#include <mutex>


BEGIN_JK_NAMESPACE

class JKReferenced;

class JK_API JKDeleteHandler
{
public:

	typedef std::pair<unsigned int, const JKReferenced*> FrameNumberObjectPair;
	typedef std::list<FrameNumberObjectPair> ObjectsToDeleteList;

	JKDeleteHandler(int numberOfFramesToRetainObjects = 0);

	virtual ~JKDeleteHandler();

	void setNumFramesToRetainObjects(unsigned int numberOfFramesToRetainObjects) { _numFramesToRetainObjects = numberOfFramesToRetainObjects; }

	unsigned int getNumFramesToRetainObjects() const { return _numFramesToRetainObjects; }

	/** Set the current frame number so that subsequent deletes get tagged as associated with this frame.*/
	void setFrameNumber(unsigned int frameNumber) { _currentFrameNumber = frameNumber; }

	/** Get the current frame number.*/
	unsigned int getFrameNumber() const { return _currentFrameNumber; }

	inline void doDelete(const JKReferenced* object) { delete object; }

	/** Flush objects that are ready to be fully deleted.*/
	virtual void flush();

	/** Flush all objects that the JKDeleteHandler holds.
	* Note, this should only be called if there are no threads running with non ref_ptr<> pointers, such as graphics threads.*/
	virtual void flushAll();

	/** Request the deletion of an object.
	* Depending on users implementation of JKDeleteHandler, the delete of the object may occur
	* straight away or be delayed until doDelete is called.
	* The default implementation does a delete straight away.*/
	virtual void requestDelete(const JKReferenced* object);

protected:

	JKDeleteHandler(const JKDeleteHandler&) :
		_numFramesToRetainObjects(0),
		_currentFrameNumber(0) {}
	JKDeleteHandler operator = (const JKDeleteHandler&) { return *this; }

	unsigned int            _numFramesToRetainObjects;
	unsigned int            _currentFrameNumber;
	std::mutex				_mutex;
	ObjectsToDeleteList     _objectsToDelete;

};

END_JK_NAMESPACE