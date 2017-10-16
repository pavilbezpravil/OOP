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
class SharedPtr {
	typedef SharedPtr<Type, Tdeleter> t_MySharedPtr;
	typedef Tdeleter t_Deleter;

private:
	Type *ptr;
	size_t *linksCounter;
	t_Deleter _del;

    void releaseInternal() {
        if (!linksCounter) { return; }
        assert(*linksCounter >= 0);
        if (*linksCounter == 1) {
            _del(ptr);
			ptr = nullptr;
			delete linksCounter;
        } else {
			--*linksCounter;
		}
		linksCounter = nullptr;
    }

public: // Constructors and destructor.

	SharedPtr() : ptr(nullptr), linksCounter(nullptr) {

    };

	SharedPtr(Type *pObj) : ptr(pObj), linksCounter(new size_t(1)) {

	}

	SharedPtr(t_MySharedPtr &&uniquePTR) { // Move constructor.
		releaseInternal();
		linksCounter = uniquePTR.linksCounter;
		ptr = uniquePTR.ptr;
	};

	SharedPtr(const t_MySharedPtr& uniquePtr) : ptr(uniquePtr.get()), linksCounter(uniquePtr.linksCounter) {
        // TODO: ++
        if (linksCounter) {
            ++*linksCounter;
        }
    }

	virtual ~SharedPtr() {
        releaseInternal();
	}

public:
	t_MySharedPtr& operator=(const t_MySharedPtr& uniquePtr) {
        if (this != &uniquePtr) {
            releaseInternal();

            ptr = uniquePtr.ptr;
            linksCounter = uniquePtr.linksCounter;
            if (linksCounter) {
                ++*linksCounter;
            }
        }
        return *this;
    }

	t_MySharedPtr& operator=(t_MySharedPtr &&MySharedPtr) {
		if (this != &MySharedPtr) {
			releaseInternal();

			linksCounter = MySharedPtr.linksCounter;
			MySharedPtr.linksCounter = nullptr;
			ptr = MySharedPtr.ptr;
			MySharedPtr.ptr = nullptr;
		}
		return *this;
	}

	t_MySharedPtr& operator=(Type *pObject) {
		if (ptr != pObject) {
			releaseInternal();
			ptr = pObject;
            linksCounter = new size_t(1);
		}
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
	void reset(Type *pObject = nullptr) { // Replace the stored pointer.
		if (ptr == pObject) { return; }

        releaseInternal();
        linksCounter = new size_t(1);
        ptr = pObject;
	}

	void swap(t_MySharedPtr &uniquePtr) { // Exchange the pointer with another object
        std::swap(ptr, uniquePtr.ptr);
        std::swap(linksCounter, uniquePtr.linksCounter);
	}
};
