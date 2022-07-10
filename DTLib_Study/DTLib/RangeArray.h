/*
 * This file is part of the DTLib template project, http://www.dt4sw.com
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 唐佐林 (Delphi Tang)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef RANGEARRAY_H
#define RANGEARRAY_H

#include "Array.h"

namespace DTLib
{

template < typename T >
class RangeArray : public Array<T>
{
protected:
    int m_lower;
    int m_upper;
public:
    RangeArray(int lower, int upper)   // O(1)
    {
        m_lower = lower;
        m_upper = upper;

        this->m_array = new T[upper - lower + 1];
    }

    RangeArray(const RangeArray<T>& obj)    // O(n)
    {
        int len = obj.length();

        m_lower = obj.m_lower;
        m_upper = obj.m_upper;

        this->m_array = new T[len];

        for(int i=0; i<len; i++)
        {
            this->m_array[i] = obj.m_array[i];
        }
    }

    bool set(int i, const T& e) // O(1)
    {
        bool ret = ((m_lower <= i) && (i <= m_upper));

        if( ret )
        {
            this->m_array[i - m_lower] = e;
        }

        return ret;
    }

    bool get(int i, T& e) const   // O(1)
    {
        bool ret = ((m_lower <= i) && (i <= m_upper));

        if( ret )
        {
            e = this->m_array[i - m_lower];
        }

        return ret;
    }

    RangeArray<T>& operator= (const RangeArray<T>& obj)  // O(n)
    {
        if( this != &obj )
        {
            int len = obj.length();
            T* toDel = this->m_array;
            T* arr = new T[len];

            for(int i=0; i<len; i++)
            {
                arr[i] = obj.m_array[i];
            }

            m_lower = obj.m_lower;
            m_upper = obj.m_upper;

            this->m_array = arr;

            delete[] toDel;
        }

        return *this;
    }

    T& operator[] (int i)   // O(1)
    {
        if((m_lower <= i) && (i <= m_upper))
        {
            return this->m_array[i - m_lower];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }

    T operator[] (int i) const  // O(1)
    {
        return (const_cast<RangeArray<T>&>(*this))[i];
    }

    int lower() const
    {
        return m_lower;
    }

    int upper() const
    {
        return m_upper;
    }

    int length() const     // O(1)
    {
        return m_upper - m_lower + 1;
    }

    ~RangeArray()
    {
        delete[] this->m_array;
    }
};

}

#endif // RANGEARRAY_H
