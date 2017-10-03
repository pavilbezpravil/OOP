#pragma once

#include <stdlib.h>
#include <cassert>
#include <algorithm>

template<class T> struct deleter {
	void operator()(T *p) {
		if (p) {
			delete p;
		}
	}
};


template<class Type, class Tdeleter = deleter<Type>>
class MySharedPtr {
	typedef MySharedPtr<Type, Tdeleter> t_MySharedPtr;
	typedef Tdeleter t_Deleter;

private:
	Type *ptr;
	size_t *linksCounter;
	t_Deleter _del;

    void releaseInternal() {
        assert(linksCounter);
        if (*linksCounter == 1) {
            _del(ptr);
            ptr = nullptr;
        }
        --*linksCounter;
    }

public: // Constructors and destructor.

	MySharedPtr() : ptr(nullptr), linksCounter(new size_t(1)) {

    };

	MySharedPtr(Type *pObj) : ptr(pObj), linksCounter(new size_t(1)) {

	}

	MySharedPtr(t_MySharedPtr &&uniquePTR) : ptr(uniquePTR.release()), linksCounter(uniquePTR.release()) { // Move constructor.

	};

	MySharedPtr(const t_MySharedPtr& uniquePtr) : ptr(uniquePtr.get()), linksCounter(uniquePtr.linksCounter) {
        // TODO: ++
        ++*linksCounter;
    }

	virtual ~MySharedPtr() {
        releaseInternal();
        assert(*linksCounter >= 0);
        if (*linksCounter == 0) {
            delete(linksCounter);
        }
	}

public:
	t_MySharedPtr& operator=(const t_MySharedPtr& uniquePtr) {
        releaseInternal();

        ptr = uniquePtr.get();
        linksCounter = uniquePtr.get_linksCounter();
        ++*linksCounter;
        return *this;
    }

	t_MySharedPtr& operator=(t_MySharedPtr &&MySharedPtr) {
        linksCounter = MySharedPtr.get_linksCounter();
        ++*linksCounter;
        ptr = MySharedPtr.release();
		return *this;
	}

	t_MySharedPtr& operator=(Type *pObject) {
        releaseInternal();
		ptr = pObject;
        if (*linksCounter == 0) {
            linksCounter = new size_t;
        }
        *linksCounter = 1;
		return *this;
	}

public: // Observers.
	Type& operator*() const { // Dereference the stored pointer.
		return *ptr;
	}

	Type* operator->() const { // Return the stored pointer.
		return ptr;
	}

	Type* get() const { // Return the stored pointer.
		return ptr;
	}

	size_t *get_linksCounter() const {
		return linksCounter;
	}

	Tdeleter& get_deleter() { // Return a reference to the stored _deleter.
		return _del;
	}

	operator bool() const { // Return false if the stored pointer is null.
		return !ptr;
	}
public: // Modifiers.
	Type *release() { // Release ownership of any stored pointer.
        --*linksCounter;

        Type *tmp = ptr;
        ptr = nullptr;
        return tmp;
	}

	void reset(Type *pObject = nullptr) { // Replace the stored pointer.
        releaseInternal();
        if (*linksCounter != 0) {
            linksCounter = new size_t;
        }
        *linksCounter = 1;
        ptr = pObject;
	}

	void swap(t_MySharedPtr &uniquePtr) { // Exchange the pointer with another object
        std::swap(ptr, uniquePtr.ptr);
        std::swap(linksCounter, uniquePtr.linksCounter);
	}
};
