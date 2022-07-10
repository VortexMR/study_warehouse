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

#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "LinuxList.h"
#include "DualLinkList.h"


namespace DTLib
{

template < typename T >
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    list_head* m_current;

    list_head* position(int i) const
    {
        list_head* ret = const_cast<list_head*>(&m_header);

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

public:
    DualCircleList()
    {
        this->m_length = 0;
        this->m_step = 1;

        m_current = NULL;

        INIT_LIST_HEAD(&m_header);
    }

    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = true;
        Node* node = new Node();

        i = i % (this->m_length + 1);

        if( node != NULL )
        {
            node->value = e;

            list_add_tail(&node->head, position(i)->next);

            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        ret = ((0 <= i) && (i < this->m_length));

        if( ret )
        {
            list_head* toDel = position(i)->next;

            if( m_current == toDel )
            {
                m_current = toDel->next;
            }

            list_del(toDel);

            this->m_length--;

            delete list_entry(toDel, Node, head);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = true;

        i = mod(i);

        ret = ((0 <= i) && (i < this->m_length));

        if( ret )
        {
            list_entry(position(i)->next, Node, head)->value = e;
        }

        return ret;
    }

    T get(int i) const
    {
        T ret;

        if( get(i, ret) )
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element ...");
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = true;

        i = mod(i);

        ret = ((0 <= i) && (i < this->m_length));

        if( ret )
        {
            e = list_entry(position(i)->next, Node, head)->value;
        }

        return ret;
    }

    int find(const T& e) const
    {
        int ret = -1;
        int i = 0;
        list_head* slider = NULL;

        list_for_each(slider, &m_header)
        {
            if( list_entry(slider, Node, head)->value == e )
            {
                ret = i;
                break;
            }

            i++;
        }

        return ret;
    }

    int length() const
    {
        return this->m_length;
    }

    void clear()
    {
        while( this->m_length > 0 )
        {
            remove(0);
        }
    }

    bool move(int i, int step = 1)
    {
        bool ret = (step > 0);

        i = mod(i);

        ret = ret && ((0 <= i) && (i < this->m_length));

        if( ret )
        {
            m_current = position(i)->next;

            this->m_step = step;
        }

        return ret;
    }

    bool end()
    {
        return (m_current == NULL) || (this->m_length == 0);
    }

    T current()
    {
        if( !end() )
        {
            return list_entry(m_current, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    bool next()
    {
        int i = 0;

        while( (i < this->m_step) && !end() )
        {
            if( m_current != &m_header )
            {
                m_current = m_current->next;
                i++;
            }
            else
            {
                m_current = m_current->next;
            }
        }

        if( m_current == &m_header )
        {
            m_current = m_current->next;
        }

        return (i == this->m_step);
    }

    bool pre()
    {
        int i = 0;

        while( (i < this->m_step) && !end() )
        {
            if( m_current != &m_header )
            {
                m_current = m_current->prev;
                i++;
            }
            else
            {
                m_current = m_current->prev;
            }
        }

        if( m_current == &m_header )
        {
            m_current = m_current->prev;
        }

        return (i == this->m_step);
    }

    ~DualCircleList()
    {
        clear();
    }

};

}

#endif // DUALCIRCLELIST_H
