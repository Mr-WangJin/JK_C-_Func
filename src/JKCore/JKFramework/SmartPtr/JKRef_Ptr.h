#pragma once

#include "JKCommon/JKCommon.h"

BEGIN_JK_NAMESPACE


template<typename T> class observer_ptr;

/** Smart pointer for handling referenced counted objects.*/
template<class T>
class JKRef_Ptr
{
public:
	typedef T element_type;

	JKRef_Ptr() : _ptr(0) {}
	JKRef_Ptr(T* ptr) : _ptr(ptr) { if (_ptr) _ptr->ref(); }
	JKRef_Ptr(const JKRef_Ptr& rp) : _ptr(rp._ptr) { if (_ptr) _ptr->ref(); }
	template<class Other> JKRef_Ptr(const JKRef_Ptr<Other>& rp) : _ptr(rp._ptr) { if (_ptr) _ptr->ref(); }
	JKRef_Ptr(observer_ptr<T>& optr) : _ptr(0) { optr.lock(*this); }
	~JKRef_Ptr() { if (_ptr) _ptr->unref();  _ptr = 0; }

	JKRef_Ptr& operator = (const JKRef_Ptr& rp)
	{
		assign(rp);
		return *this;
	}

	template<class Other> JKRef_Ptr& operator = (const JKRef_Ptr<Other>& rp)
	{
		assign(rp);
		return *this;
	}

	inline JKRef_Ptr& operator = (T* ptr)
	{
		if (_ptr == ptr) return *this;
		T* tmp_ptr = _ptr;
		_ptr = ptr;
		if (_ptr) _ptr->ref();
		// unref second to prevent any deletion of any object which might
		// be referenced by the other object. i.e rp is child of the
		// original _ptr.
		if (tmp_ptr) tmp_ptr->unref();
		return *this;
	}

#ifdef OSG_USE_REF_PTR_IMPLICIT_OUTPUT_CONVERSION
		// implicit output conversion
		operator T*() const { return _ptr; }
#else
	// comparison operators for JKRef_Ptr.
	bool operator == (const JKRef_Ptr& rp) const { return (_ptr == rp._ptr); }
	bool operator == (const T* ptr) const { return (_ptr == ptr); }
	friend bool operator == (const T* ptr, const JKRef_Ptr& rp) { return (ptr == rp._ptr); }

	bool operator != (const JKRef_Ptr& rp) const { return (_ptr != rp._ptr); }
	bool operator != (const T* ptr) const { return (_ptr != ptr); }
	friend bool operator != (const T* ptr, const JKRef_Ptr& rp) { return (ptr != rp._ptr); }

	bool operator < (const JKRef_Ptr& rp) const { return (_ptr < rp._ptr); }


	// follows is an implmentation of the "safe bool idiom", details can be found at:
	//   http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Safe_bool
	//   http://lists.boost.org/Archives/boost/2003/09/52856.php

private:
	typedef T* JKRef_Ptr::*unspecified_bool_type;

public:
	// safe bool conversion
	operator unspecified_bool_type() const { return valid() ? &JKRef_Ptr::_ptr : 0; }
#endif

	T& operator*() const { return *_ptr; }
	T* operator->() const { return _ptr; }
	T* get() const { return _ptr; }

	bool operator!() const { return _ptr == 0; } // not required
	bool valid() const { return _ptr != 0; }

	/** release the pointer from ownership by this JKRef_Ptr<>, decrementing the objects refencedCount() via unref_nodelete() to prevent the Object
	* object from being deleted even if the reference count goes to zero.  Use when using a local JKRef_Ptr<> to an Object that you want to return
	* from a function/method via a C pointer, whilst preventing the normal JKRef_Ptr<> destructor from cleaning up the object. When using release()
	* you are implicitly expecting other code to take over management of the object, otherwise a memory leak will result. */
	T* release() { T* tmp = _ptr; if (_ptr) _ptr->unref_nodelete(); _ptr = 0; return tmp; }

	void swap(JKRef_Ptr& rp) { T* tmp = _ptr; _ptr = rp._ptr; rp._ptr = tmp; }

private:

	template<class Other> void assign(const JKRef_Ptr<Other>& rp)
	{
		if (_ptr == rp._ptr) return;
		T* tmp_ptr = _ptr;
		_ptr = rp._ptr;
		if (_ptr) _ptr->ref();
		// unref second to prevent any deletion of any object which might
		// be referenced by the other object. i.e rp is child of the
		// original _ptr.
		if (tmp_ptr) tmp_ptr->unref();
	}

	template<class Other> friend class JKRef_Ptr;

	T* _ptr;
};


template<class T> inline
	void swap(JKRef_Ptr<T>& rp1, JKRef_Ptr<T>& rp2) { rp1.swap(rp2); }

template<class T> inline
	T* get_pointer(const JKRef_Ptr<T>& rp) { return rp.get(); }

template<class T, class Y> inline
	JKRef_Ptr<T> static_pointer_cast(const JKRef_Ptr<Y>& rp) { return static_cast<T*>(rp.get()); }

template<class T, class Y> inline
	JKRef_Ptr<T> dynamic_pointer_cast(const JKRef_Ptr<Y>& rp) { return dynamic_cast<T*>(rp.get()); }

template<class T, class Y> inline
	JKRef_Ptr<T> const_pointer_cast(const JKRef_Ptr<Y>& rp) { return const_cast<T*>(rp.get()); }

END_JK_NAMESPACE