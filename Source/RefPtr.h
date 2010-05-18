/*
 *  RefPtr.h
 *  PixelKit
 *
 *  Created by Keishi Hattori on 5/15/10.
 *  Copyright 2010 Keishi Hattori. All rights reserved.
 *
 */

#ifndef RefPtr_h
#define RefPtr_h

namespace PixelKit {
    template <typename T> class RefPtr {
    public:
        RefPtr() : m_ptr(NULL), m_refCount(-1) {}
        RefPtr(T* ptr);
        RefPtr(const RefPtr<T>& ptr);
        virtual ~RefPtr();
        
        const RefPtr<T>& operator=(T* ptr);
        const RefPtr<T>& operator=(const RefPtr<T>& ptr);
        const T& operator*();
        T* const operator->();
        operator T*() { return m_ptr; }
        
        void retain();
        void release();
    private:
        T* m_ptr;
        int m_refCount;
    };
    
    template<typename T> inline const RefPtr<T>& RefPtr<T>::operator=(T* ptr)
    {
        release();
        m_ptr = ptr;
        m_refCount = m_ptr ? 1 : -1;
        return *this;
    }
    
    template<typename T> inline const RefPtr<T>& RefPtr<T>::operator=(const RefPtr<T>& ptr)
    {
        release();
        m_ptr = ptr.m_ptr;
        m_refCount = ptr.m_refCount;
        retain();
        return *this;
    }
    
    template<typename T> inline const T& RefPtr<T>::operator*()
    {
        return *m_ptr;
    }
    
    template<typename T> inline T* const RefPtr<T>::operator->()
    {
        return m_ptr;
    }
    
    template<typename T> inline RefPtr<T>::RefPtr(T* ptr)
    {
        m_ptr = ptr;
        m_refCount = m_ptr ? 1 : -1;
    }
    template<typename T> inline RefPtr<T>::RefPtr(const RefPtr<T>& ptr)
    {
        m_ptr = ptr.m_ptr;
        m_refCount = ptr.m_refCount;
    }
    template<typename T> inline RefPtr<T>::~RefPtr()
    {
        release();
    }
    template<typename T> inline void RefPtr<T>::release()
    {
        if (m_refCount < 1)
            return;
        m_refCount--;
        if (m_refCount == 0) {
            if (m_ptr) {
                delete m_ptr;
                m_ptr = NULL;
            }
        }
    }
    template<typename T> inline void RefPtr<T>::retain()
    {
        if (m_refCount > -1) {
            m_refCount++;
        }
    }
}

#endif
