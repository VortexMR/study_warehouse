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

#ifndef STATICMATRIX_H
#define STATICMATRIX_H

#include "Matrix.h"
#include "StaticArray.h"

namespace DTLib
{

template < typename T, int ROW, int COL >
class StaticMatrix : public Matrix<T>, public StaticArray< StaticArray<T, COL>, ROW >
{
public:
    int row() const
    {
        return ROW;
    }

    int col() const
    {
        return COL;
    }

    bool set(int i, const T& e)
    {
        return set(i/COL, i%COL, e);
    }

    bool set(int r, int c, const T& e)
    {
        bool ret = (0 <= r) && (r < ROW) && (0 <= c) && (c < COL);

        if( ret )
        {
            this->m_array[r][c] = e;
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        return get(i/COL, i%COL, e);
    }

    bool get(int r, int c, T& e) const
    {
        bool ret = (0 <= r) && (r < ROW) && (0 <= c) && (c < COL);

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

template < typename T, int ROW, int COL >
StaticMatrix<T, ROW, COL> operator * (const T& l, const StaticMatrix<T, ROW, COL>& r)
{
    StaticMatrix<T, ROW, COL> ret;

    r.multiply(l, ret);

    return ret;
}

template < typename T, int ROW, int COL >
StaticMatrix<T, ROW, COL> operator * (const StaticMatrix<T, ROW, COL>& l, const T& r)
{
    StaticMatrix<T, ROW, COL> ret;

    l.multiply(r, ret);

    return ret;
}

template < typename T, int ROW, int CR, int COL >
StaticMatrix<T, ROW, COL> operator * (const StaticMatrix<T, ROW, CR>& l, const StaticMatrix<T, CR, COL>& r)
{
    StaticMatrix<T, ROW, COL> ret;

    l.multiply(r, ret);

    return ret;
}

template < typename T, int ROW, int COL >
StaticMatrix<T, ROW, COL> operator + (const StaticMatrix<T, ROW, COL>& l, const StaticMatrix<T, ROW, COL>& r)
{
    StaticMatrix<T, ROW, COL> ret;

    l.add(r, ret);

    return ret;
}

template < typename T, int ROW, int COL >
StaticMatrix<T, ROW, COL> operator - (const StaticMatrix<T, ROW, COL>& l, const StaticMatrix<T, ROW, COL>& r)
{
    StaticMatrix<T, ROW, COL> ret;

    l.minus(r, ret);

    return ret;
}

}


#endif // STATICMATRIX_H
