#pragma once


#include "JKCommon/JKCommon.h"

BEGIN_JK_NAMESPACE

template <class T>
class JKSharedPtr
{
public:
	//赋值构造函数
	JKSharedPtr(T* p = NULL) :_ptr(p), _use(new size_t(1)) {}

	//赋值构造函数
	JKSharedPtr(const JKSharedPtr<T>& rhs) :_ptr(rhs._ptr), _use(rhs._use) { ++*_use; }

	//析构
	~JKSharedPtr(void) { _unref(); }

	//引用
	T& operator*();
	T* operator->();
	const T& operator*() const;
	const T* operator->() const;

	//重载赋值操作符
	JKSharedPtr& operator=(const JKSharedPtr& rhs);

	//取值
	T* Get() { return _ptr; }
	const T* Get() const { return _ptr; }

	//空值判断
	bool IsNull()const { return NULL == _ptr; }
private:
	T* _ptr;
	size_t* _use;

	void _unref()
	{
		if (--*_use == 0)
		{
			SAFE_DELETE(_ptr);
			SAFE_DELETE(_use);
		}
	}
};

template<class T>
inline T& JKSharedPtr<T>::operator*()
{
	if (_ptr)
	{
		return *_ptr;
	}

	throw std::runtime_error("null _ptr error");
}

template<class T>
inline T* JKSharedPtr<T>::operator->()
{
	if (_ptr)
	{
		return _ptr;
	}

	throw std::runtime_error("null _ptr error");
}

template<class T>
inline const T& JKSharedPtr<T>::operator*() const
{
	if (_ptr)
	{
		return *_ptr;
	}

	throw std::runtime_error("null _ptr error");
}

template<class T>
inline const T* JKSharedPtr<T>::operator->() const
{
	if (_ptr)
	{
		return _ptr;
	}

	throw std::runtime_error("null _ptr error");
}

template<class T>
JKSharedPtr<T>& JKSharedPtr<T>::operator=(const JKSharedPtr<T>& rhs)
{
	++*rhs._use;
	_unref();
	_ptr = rhs._ptr;
	_use = rhs._use;

	return *this;
}

END_JK_NAMESPACE