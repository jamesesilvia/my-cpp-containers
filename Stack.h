#ifndef STACK_H
#define STACK_H

#include <cassert>
#include <algorithm>

template<class T>
T* NewCopy(const T* src, size_t srcsize, size_t destsize)
{
    assert(destsize >= srcsize);
    T* dest = new T[destsize];
    try
    {
        std::copy(src, src+srcsize, dest);
    }
    catch(...)
    {
        delete[] dest;
        throw;
    }
    return dest;
}

template<class T>
class StackImp
{
protected:
    T* _v;
    size_t _vsize;
    size_t _vused;

    StackImp(size_t size)
        : _v(static_cast<T*> ( size == 0 ? 0 : operator new(sizeof(T)*size)))
        , _vsize(size)
        , _vused(0)
        { }

    ~StackImp()
    {
        destroy(_v, _v + _vused);
        operator delete(_v);
    }

    void Swap(const StackImp& other)
    {
        std::swap(_v, other._v);
        std::swap(_vsize, other._vsize);
        std::swap(_vused, other._vused);
    }

private:
    StackImp(const StackImp&);
    StackImp& operator=(const StackImp&);
};


template<class T>
class Stack
{
    T* _v;
    size_t _vsize;
    size_t _vused;

public:
    Stack(size_t size = 10)
        : _v(new T[size])
        , _vsize(size)
        , _vused(0)
        { }

    ~Stack()
    {
        delete[] _v;
    }

    Stack(const Stack& other)
        : _v(NewCopy(other._v, other._vsize, other._vsize))
        , _vsize(other._vsize)
        , _vused(other._vused)
        { }

#if 0
    Stack& operator=(const Stack& other)
    {
        if (*this != &other)
        {
            auto v_new = NewCopy(other._v, other._vsize, other._vsize);
            delete[] _v;
            _v = v_new;
            _vsize = other._vsize;
            _vused = other._vused;
        }
        return *this;
    }
#endif

    bool Empty() const
    {
        return _vused == 0;
    }

    size_t Count() const
    {
        return _vused;
    }

    void push(const T& t)
    {
        if (_vsize == _vused)
        {
            auto newSize = getNewSize();
            auto v_new = NewCopy(_v, _vsize, newSize);
            _v = v_new;
            _vsize = newSize;
        }
        _v[_vused] = t;
        ++_vused;
    }

    const T& Top() const
    {
        if (Empty())
        {
            throw "empty stack";
        }
        else
        {
            return _v[_vused - 1];
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
            --_vused;
        }
    }

private:
    
    size_t getNewSize() const
    {
        return _vsize*2 + 1;
    }
};

#endif