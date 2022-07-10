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

#ifndef DYNAMICMATRIX_H
#define DYNAMICMATRIX_H

#include "Matrix.h"
#include "DynamicArray.h"

namespace DTLib
{

template < typename T >
class DynamicMatrix : public Matrix<T>, public DynamicArray< DynamicArray<T> >
{
protected:
    int m_col;

public:
    DynamicMatrix(int row = 0, int col = 0) :  DynamicArray< DynamicArray<T> >(row), m_col(col)
    {
        format();
    }

    int row() const
    {
        return this->length();
    }

    int col() const
    {
        return m_col;
    }

    void resize(int row, int col)
    {
        if( row != this->length() )
        {
            DynamicArray< DynamicArray<T> >::resize(row);
        }

        if( col != m_col )
        {
            m_col = col;

            format();
        }
    }

    void format()
    {
        for(int i=0; i<row(); i++)
        {
            (*this)[i].resize(m_col);
        }
    }

    bool set(int i, const T& e)
    {
        return set(i/m_col, i%m_col, e);
    }

    bool set(int r, int c, const T& e)
    {
        bool ret = (0 <= r) && (r < this->length()) && (0 <= c) && (c < m_col);

        if( ret )
        {
            this->m_array[r][c] = e;
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        return get(i/m_col, i%m_col, e);
    }

    bool get(int r, int c, T& e) const
    {
        bool ret = (0 <= r) && (r < this->length()) && (0 <= c) && (c < m_col);

        if( ret )
        {
            e = this->m_array[r][c];
        }

        return ret;
    }

    T operator()(int i, int j) const
    {
        return this->m_array[i][j];
    }

    T& operator()(int i, int j)
    {
        return this->m_array[i][j];
    }
};

template < typename T >
DynamicMatrix<T> operator * (const T& l, const DynamicMatrix<T>& r)
{
    DynamicMatrix<T> ret(r.row(), r.col());

    if( !r.multiply(l, ret) )
    {
        THROW_EXCEPTION(InvalidOperationException, "Parameter is NOT the valid shape ...");
    }

    return ret;
}

template < typename T >
DynamicMatrix<T> operator * (const DynamicMatrix<T>& l, const T& r)
{
    DynamicMatrix<T> ret(l.row(), l.col());

    if( !l.multiply(r, ret) )
    {
        THROW_EXCEPTION(InvalidOperationException, "Parameter is NOT the valid shape ...");
    }

    return ret;
}

template < typename T >
DynamicMatrix<T> operator * (const DynamicMatrix<T>& l, const DynamicMatrix<T>& r)
{
    DynamicMatrix<T> ret(l.row(), r.col());

    if( !l.multiply(r, ret) )
    {
        THROW_EXCEPTION(InvalidOperationException, "Parameter is NOT the valid shape ...");
    }

    return ret;
}

template < typename T >
DynamicMatrix<T> operator + (const DynamicMatrix<T>& l, const DynamicMatrix<T>& r)
{
    DynamicMatrix<T> ret(l.row(), l.col());

    if( !l.add(r, ret) )
    {
        THROW_EXCEPTION(InvalidOperationException, "Parameter is NOT the valid shape ...");
    }

    return ret;
}

template < typename T >
DynamicMatrix<T> operator - (const DynamicMatrix<T>& l, const DynamicMatrix<T>& r)
{
    DynamicMatrix<T> ret(l.row(), l.col());

    if( !l.minus(r, ret) )
    {
        THROW_EXCEPTION(InvalidOperationException, "Parameter is NOT the valid shape ...");
    }

    return ret;
}

}

#endif // DYNAMICMATRIX_H
