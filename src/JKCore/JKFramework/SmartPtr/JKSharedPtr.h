#pragma once


#include "JKCommon/JKCommon.h"

BEGIN_JK_NAMESPACE

template <class T>
class JKSharedPtr
{
public:
	//��ֵ���캯��
	JKSharedPtr(T* p = NULL) :_ptr(p), _use(new size_t(1)) {}

	//��ֵ���캯��
	JKSharedPtr(const JKSharedPtr<T>& rhs) :_ptr(rhs._ptr), _use(rhs._use) { ++*_use; }

	//����
	~JKSharedPtr(void) { _unref(); }

	//����
	T& operator*();
	T* operator->();
	const T& operator*() const;
	const T* operator->() const;

	//���ظ�ֵ������
	JKSharedPtr& operator=(const JKSharedPtr& rhs);

	//ȡֵ
	T* Get() { return _ptr; }
	const T* Get() const { return _ptr; }

	//��ֵ�ж�
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