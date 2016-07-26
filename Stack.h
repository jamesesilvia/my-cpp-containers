#ifndef STACK_H
#define STACK_H

#include <cassert>
#include <algorithm>

// as seen in exceptional c++
template <class T1, class T2>
void construct(T1* p, const T2& value)
{
    new (p) T1(value);
}

template <class T>
void destroy(T* p)
{
    p->~T();
}

template <class FwdIter>
void destroy(FwdIter first, FwdIter last)
{
    while (first != last)
    {
        destroy(&*first);
        ++first;
    }
}


template <class T>
void swap(T& a, T& b)
{
    T temp(a);
    a = b;
    b = temp;
}
// as seen in exceptional c++


template<class T>
class StackImpl
{
public:
    T* m_pT;
    size_t m_size;
    size_t m_used;

    StackImpl(size_t size)
        : m_pT(static_cast<T*> ( size == 0 ? 0 : operator new(sizeof(T)*size)))
        , m_size(size)
        , m_used(0)
        { }

    ~StackImpl()
    {
        destroy(m_pT, m_pT + m_used);
        operator delete(m_pT);
    }

    void Swap(StackImpl& other)
    {
        swap(m_pT, other.m_pT);
        swap(m_size, other.m_size);
        swap(m_used, other.m_used);
    }

private:
    StackImpl(const StackImpl&);
    StackImpl& operator=(const StackImpl&);
};


template<class T>
class Stack
{

public:
    Stack(size_t size = 0)
        : m_stackImpl(size)
        { }

    ~Stack() = default;

    Stack(const Stack& other)
        : m_stackImpl(other.m_stackImpl.m_used)
    {
        while (m_stackImpl.used < other.m_stackImpl.m_used)
        {
            construct(m_stackImpl.m_pT + m_stackImpl.m_used,
                      other.m_stackImpl.m_pT[m_stackImpl.m_used]);
            ++m_stackImpl.m_used;
        }
    }

    Stack& operator=(const Stack& other)
    {
        Stack temp(other);
        m_stackImpl.Swap(temp.m_stackImpl);
        return *this;
    }

    bool Empty() const
    {
        return (m_stackImpl.m_used == 0);
    }

    size_t Count() const
    {
        return m_stackImpl.m_used;
    }

    void push(const T& t)
    {
        if (m_stackImpl.m_size == m_stackImpl.m_used)
        {
            Stack temp(getNewSize());
            while (temp.Count() < m_stackImpl.m_used)
            {
                temp.push(m_stackImpl.m_pT[temp.Count()]);
            }
            temp.push(t);
            m_stackImpl.Swap(temp.m_stackImpl);
        }
        else
        {
            construct(m_stackImpl.m_pT + m_stackImpl.m_used, t);
            ++m_stackImpl.m_used;
        }
    }

    T& Top()
    {
        if (Empty())
        {
            throw "empty stack";
        }
        else
        {
            return m_stackImpl.m_pT[m_stackImpl.m_used - 1];
        }
    }

    void Pop()
    {
        if (Empty())
        {
            throw "pop empty stack";
        }
        else
        {
            --m_stackImpl.m_used;
            destroy(m_stackImpl.m_pT + m_stackImpl.m_used);
        }
    }

private:
    StackImpl<T> m_stackImpl;

    size_t getNewSize()
    {
        return (2*m_stackImpl.m_used + 1);
    }

#if 0
    const T& Top() const
    {
        if (Empty())
        {
            throw "empty stack";
        }
        else
        {
            return this->m_pT[this->m_used - 1];
        }
    }

    void Pop()
    {
        if (Empty())
        {
            throw "pop empty stack";
        }
        else
        {
            --this->m_used;
        }
    }

private:
    StackImpl<T> m_stackImpl;
    
    size_t getNewSize() const
    {
        return this->m_size*2 + 1;
    }
#endif
};

#endif