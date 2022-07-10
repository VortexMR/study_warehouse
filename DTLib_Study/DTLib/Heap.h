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


#ifndef HEAP_H
#define HEAP_H

#include "Queue.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class Heap : public Queue<T>
{
protected:
    bool m_isMax;
    int m_length;

    virtual bool compare(const T& lv, const T& rv)
    {
        return m_isMax ? (lv > rv) : (lv < rv);
    }

    virtual T& get(int i) = 0;

    T& get(int i) const
    {
        return const_cast< Heap<T>* >(this)->get(i);
    }

    int left(int i) const
    {
        return 2 * i;
    }

    int right(int i) const
    {
        return 2 * i + 1;
    }

    int parent(int i) const
    {
        return i / 2;
    }
public:
    Heap(bool isMax)
    {
        m_isMax = isMax;
        m_length = 0;
    }

    void add(const T& e)
    {
        int i = length() + 1;

        if( i <= capacity() )
        {
            while( (i > 1) && compare(e, get(parent(i))) )
            {
                get(i) = get(parent(i));

                i = parent(i);
            }

            get(i) = e;

            m_length++;
        }
    }

    T front() const   // O(1)
    {
        if( length() > 0 )
        {
            return get(1);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Heap is empty ...");
        }
    }

    bool front(T& e) const
    {
        bool ret = (length() > 0);

        if( ret )
        {
            e = front();
        }

        return ret;
    }

    void remove()
    {
        if( length() > 0 )
        {
            T& e = get(length());
            int i = 1;
            int ci = left(i);

            while( ci < length() )
            {
                if( ((ci + 1) < length()) && compare(get(ci + 1), get(ci)) )
                {
                    ci++;
                }

                if( !compare(get(ci), e) )
                {
                    break;
                }
                else
                {
                    get(i) = get(ci);
                    i = ci;
                    ci = left(i);
                }
            }

            get(i) = e;

            m_length--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Heap is empty ...");
        }
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        m_length = 0;
    }

    virtual int capacity() const = 0;
};

}

#endif // HEAP_H
