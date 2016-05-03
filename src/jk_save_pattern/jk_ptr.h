#ifndef __JK_PTR_HPP_INCLUDED__
#define __JK_PTR_HPP_INCLUDED__

#include "jk_assert.hpp"

namespace jk {

// Template pointer, does not take ownership of an object.
template <typename T>
class Ptr {
  public:

	explicit Ptr(T* p = NULL)
	: ptr_(p) {
	}

	T* Get() const {						
		return ptr_;
	}

	Ptr<T>& operator=(T* p) {
		ptr_ = p;
		return *this;
	}

	T* operator->() const {						
		JK_TEST_ASSERT(ptr_ != NULL, "Attempt to use operator -> on NULL pointer.");
		return ptr_;
	}

	T& operator* () const { 
		JK_TEST_ASSERT(ptr_ != NULL, "Attempt to use operator * on NULL pointer.");
		return *ptr_;
	}

private:
	T*	ptr_;
};

} // namespace jk

#endif // __JK_PTR_HPP_INCLUDED__
