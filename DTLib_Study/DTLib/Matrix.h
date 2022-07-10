#ifndef MATRIX_H
#define MATRIX_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class Matrix : public Object
{
public:
    virtual int row() const = 0;
    virtual int col() const = 0;
    virtual bool get(int r, int c, T& e) const = 0;
    virtual bool set(int r, int c, const T& e) = 0;
    virtual bool get(int i, T& e) const = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual T operator()(int i, int j) const = 0;
    virtual T& operator()(int i, int j) = 0;

    bool multiply(const T& v, Matrix<T>& r) const
    {
        const Matrix<T>& self = *this;
        bool ret = (self.row() == r.row()) && (self.col() == r.col());

        if( ret )
        {
            for(int i=0; i<self.row(); i++)
            {
                for(int j=0; j<self.col(); j++)
                {
                    r(i, j) = v * self(i, j);
                }
            }
        }

        return ret;
    }

    bool multiply(const Matrix<T>& m, Matrix<T>& r) const
    {
        const Matrix<T>& self = *this;
        bool ret = (self.col() == m.row()) && (self.row() == r.row()) && (m.col() == r.col());

        if( ret )
        {
            T* tmp = new T[self.row() * r.col()];

            if( tmp != NULL )
            {
                for(int i=0; i<self.row(); i++)
                {
                    for(int j=0; j<m.col(); j++)
                    {
                        T& v = tmp[r.col() * i + j];

                        v = 0;

                        for(int k=0; k<m.row(); k++)
                        {
                            v += self(i, k) * m(k, j);
                        }

                    }
                }

                for(int i=0; i<r.row(); i++)
                {
                    for(int j=0; j<r.col(); j++)
                    {
                        r(i, j) = tmp[r.col() * i + j];
                    }
                }

                delete[] tmp;
            }
            else
            {

            }
        }

        return ret;
    }

    bool add(const Matrix<T>& m, Matrix<T>& r) const
    {
        const Matrix<T>& self = *this;
        bool ret = (self.row() == m.row()) && (self.row() == r.row()) && (self.col() == m.col()) && (self.col() == r.col());

        if( ret )
        {
            for(int i=0; i<self.row(); i++)
            {
                for(int j=0; j<self.col(); j++)
                {
                    r(i, j) = self(i, j) + m(i, j);
                }
            }
        }

        return ret;
    }

    bool minus(const Matrix<T>& m, Matrix<T>& r) const
    {
        const Matrix<T>& self = *this;
        bool ret = (self.row() == m.row()) && (self.row() == r.row()) && (self.col() == m.col()) && (self.col() == r.col());

        if( ret )
        {
            for(int i=0; i<self.row(); i++)
            {
                for(int j=0; j<self.col(); j++)
                {
                    r(i, j) = self(i, j) - m(i, j);
                }
            }
        }

        return ret;
    }

    bool transpose(Matrix<T>& r) const
    {
        const Matrix<T>& self = *this;
        bool ret = (self.row() == r.col()) && (self.col() == r.row());

        if( ret )
        {
            for(int i=0; i<self.row(); i++)
            {
                for(int j=0; j<self.col(); j++)
                {
                    r(j, i) = self(i, j);
                }
            }
        }

        return ret;
    }

    bool sub(int i, int j, Matrix<T>& r) const
    {
        const Matrix<T>& self = *this;
        bool ret = (self.row() == (r.row() + 1)) && (self.col() == (r.col() + 1));

        if( ret )
        {
            int index = 0;

            for(int si=0; si<self.row(); si++)
            {
                if( si == i ) continue;

                for(int sj=0; sj<self.col(); sj++)
                {
                    if( sj == j ) continue;

                    r.set(index++, self(si, sj));
                }
            }
        }

        return ret;
    }
};

}

#endif // MATRIX_H
