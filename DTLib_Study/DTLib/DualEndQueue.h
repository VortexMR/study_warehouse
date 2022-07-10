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

#ifndef DUALENDQUEUE_H
#define DUALENDQUEUE_H

#include "LinkQueue.h"

namespace DTLib
{

template < typename T >
class DualEndQueue : public LinkQueue<T>
{
    typedef typename LinkQueue<T>::Node Node;
public:
    void push(const T& e)     // O(1)
    {
        Node* node = new Node();

        if( node != NULL )
        {
            node->value = e;

            list_add(&node->head, &this->m_header);   // O(1)

            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add new element ...");
        }
    }

    void dismiss()      // O(1)
    {
        if( this->m_length > 0 )
        {
            list_head* toDel = this->m_header.prev;

            list_del(toDel);

            this->m_length--;

            delete list_entry(toDel, Node, head);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T back() const    // O(1)
    {
        if( this->m_length > 0 )
        {
            return list_entry(this->m_header.prev, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }
};

}

#endif // DUALENDQUEUE_H
