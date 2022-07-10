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


#ifndef DYNAMICHEAP_H
#define DYNAMICHEAP_H

#include "DynamicArray.h"
#include "Heap.h"

namespace DTLib
{

template< typename T >
class DynamicHeap : public Heap<T>
{
protected:
    DynamicArray<T> m_array;

    T& get(int i)
    {
        return m_array[i-1];
    }
public:
    DynamicHeap(int capacity, bool isMax = true) : Heap<T>(isMax), m_array(capacity)
    {

    }

    int capacity() const
    {
        return m_array.length();
    }

    void resize(int nc)
    {
        m_array.resize(nc);

        this->m_length = (this->m_length < nc) ? this->m_length : nc;
    }
};

}

#endif // DYNAMICHEAP_H
