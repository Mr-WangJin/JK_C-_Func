#ifndef __JK_SCOPEDPTR_HPP_INCLUDED__
#define __JK_SCOPEDPTR_HPP_INCLUDED__

#include "jk_assert.hpp"

namespace jk {

// Scoped pointer, takes ownership of an object, could not be copied.
template <typename T>
class ScopedPtr {
  public:

	explicit ScopedPtr(T* p = NULL)
	: ptr_(p) {
	}

	ScopedPtr<T>& operator=(T* p) {						
		if(ptr_ != p)
		{
			delete ptr_;
			ptr_ = p;
		}
							
		return *this;
	}

	~ScopedPtr() {							
		delete ptr_;
	}

	T* Get() const {						
		return ptr_;
	}

	T* operator->() const
	{						
		JK_TEST_ASSERT(ptr_ != NULL, "Attempt to use operator -> on NULL pointer.");
		return ptr_;
	}

	T& operator* () const { 
		JK_TEST_ASSERT(ptr_ != NULL, "Attempt to use operator * on NULL pointer.");
		return *ptr_;
	}
	
	// Release ownership of the object to the caller.
	T* Release() {
		T* p = ptr_;
		ptr_ = NULL;
		return p;
	}

private:
	T*	ptr_;

	// Copy is prohibited:
	ScopedPtr(const ScopedPtr<T>& rhs);
	ScopedPtr<T>& operator=(const ScopedPtr<T>& rhs);
};

} // namespace jk

#endif // __JK_SCOPEDPTR_HPP_INCLUDED__
