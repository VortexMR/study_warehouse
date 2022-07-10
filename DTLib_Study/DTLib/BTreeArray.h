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

#ifndef BTREEARRAY_H
#define BTREEARRAY_H

#include "RangeArray.h"

namespace DTLib
{

template < typename T >
class BTreeArray : public Array<T>
{
protected:
    RangeArray<T> m_value;
    RangeArray<int> m_mark;
    int m_toplimit;

    int height(int i) const
    {
        int ret = 0;

        if( !isNull(i) )
        {
            int lh = height(left(i));
            int rh = height(right(i));

            ret = ((lh > rh) ? lh : rh) + 1;
        }

        return ret;
    }
public:
    BTreeArray(int toplimit) : m_value(1, (1 << toplimit)-1), m_mark(m_value.lower(), m_value.upper()), m_toplimit(toplimit)
    {
        for(int i=m_mark.lower(); i<=m_mark.upper(); i++)
        {
            m_mark[i] = 0;
        }

        this->m_array = NULL;
    }

    BTreeArray(const BTreeArray<T>& obj) : m_value(obj.m_value), m_mark(obj.m_mark), m_toplimit(obj.m_toplimit)
    {
        this->m_array = NULL;
    }

    BTreeArray<T>& operator= (const BTreeArray<T>& obj)  // O(n)
    {
        if( this != &obj )
        {
            m_value = obj.m_value;
            m_mark = obj.m_mark;
            m_toplimit = obj.m_toplimit;
        }

        return *this;
    }

    bool set(int i, const T& e) // O(1)
    {
        int tmp = 0;
        bool ret = m_mark.get(i, tmp) && ((i == 1) || m_mark[parent(i)]);

        if( ret )
        {
            m_value[i] = e;
            m_mark[i] = 1;
        }

        return ret;
    }

    bool get(int i, T& e) const   // O(1)
    {
        int tmp = 0;
        bool ret = m_mark.get(i, tmp) && m_mark[i];

        if( ret )
        {
            e = m_value[i];
        }

        return ret;
    }

    void remove(int i)
    {
        if( (m_mark.lower() <= i) && (i <= m_mark.upper()) && m_mark[i] )
        {
            m_mark[i] = 0;

            remove(left(i));
            remove(right(i));
        }
    }

    void resize(int toplimit)
    {
        if( m_toplimit != toplimit )
        {
            int len = ((1 << toplimit) - 1);
            RangeArray<T> value(1, len);
            RangeArray<int> mark(1, len);

            for(int i=mark.lower(); i<=mark.upper(); i++)
            {
                mark[i] = 0;
            }

            len = (len < length()) ? len : length();

            for(int i=1; i<=len; i++)
            {
                value[i] = m_value[i];
                mark[i] = m_mark[i];
            }

            m_value = value;
            m_mark = mark;
            m_toplimit = toplimit;
        }
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

    bool isNull(int i) const
    {
        return !((1 <= i) && (i <= length()) && m_mark[i]);
    }

    int find(const T& e) const // O(n)
    {
        int ret = 0;

        for(int i=m_value.lower(); i<=m_value.upper(); i++)
        {
            if( m_mark[i] && (m_value[i] == e) )
            {
                ret = i;
                break;
            }
        }

        return ret;
    }

    void clear()
    {
        remove(1);
    }

    T& operator[] (int i)   // O(1)
    {
        if( m_mark[i] )
        {
            return m_value[i];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Point i is invalid ...");
        }
    }

    T operator[] (int i) const  // O(1)
    {
        return (const_cast<BTreeArray<T>&>(*this))[i];
    }

    int toplimit() const
    {
        return m_toplimit;
    }

    int height() const
    {
        return height(1);
    }

    int count() const   // O(n)
    {
        int ret = 0;

        for(int i=m_mark.lower(); i<=m_mark.upper(); i++)
        {
            ret += m_mark[i];
        }

        return ret;
    }

    int length() const     // O(1)
    {
        return m_value.length();
    }
};

}

#endif // BTREEARRAY_H
