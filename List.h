#ifndef LIST_H
#define LIST_H

#include <stdexcept>
#include <initializer_list>

template<class T>
struct ListItem
{
    T* m_pT = nullptr;
    ListItem<T>* next = nullptr;
    ListItem<T>* prev = nullptr;

    ListItem() = default;

    ListItem(const T& t)
        : m_pT(new T(t))
        { }
    
    ~ListItem()
    {
        next = nullptr;
        prev = nullptr;
        delete m_pT;
    }
};

template<class T>
class ListImpl
{
public:
    ListItem<T>* m_pItemFront = nullptr;
    ListItem<T>* m_pItemLast = nullptr;
    size_t m_used = 0;
    
    ListImpl() = default;
    
    ~ListImpl()
    {
        auto temp = m_pItemFront;
        while (temp)
        {
            temp = m_pItemFront->next;
            delete m_pItemFront;
            m_pItemFront = temp;
        }
    }

    size_t empty() const
    {
        return (m_used == 0);
    }

    void push_front(const T& t)
    {
        if (empty())
        {
            m_pItemFront = m_pItemLast = new ListItem<T>(t);
            ++m_used;
        }
        else
        {
            auto pNew = new ListItem<T>(t);
            pNew->next = m_pItemFront;
            m_pItemFront->prev = pNew;
            m_pItemFront = pNew;
            ++m_used;
        }
    }

    void push_back(const T& t)
    {
        if (empty())
        {
            push_front(t);
        }
        else
        {
            auto pNew = new ListItem<T>(t);
            pNew->prev = m_pItemLast;
            m_pItemLast->next = pNew;
            m_pItemLast = pNew;
            ++m_used;
        }
    }

    void pop_front()
    {
        if (empty())
        {
            throw std::length_error("empty list pop front");
        }
        else
        {
            auto pToRemove = m_pItemFront;
            auto pNext = pToRemove->next;
            if (pNext)
            {
                pNext->prev = nullptr;
                m_pItemFront = pNext;
            }
            else
            {
                m_pItemFront = m_pItemLast = nullptr;
            }
            --m_used;
            delete pToRemove;
        }
    }

    void pop_back()
    {
        if (empty())
        {
            throw std::length_error("empty list pop front");
        }
        else
        {
            auto pToRemove = m_pItemLast;
            auto pPrev = pToRemove->prev;
            if (pPrev)
            {
                pPrev->next = nullptr;
                m_pItemLast = pPrev;
            }
            else
            {
                m_pItemLast = m_pItemFront = nullptr;
            }
            --m_used;
            delete pToRemove;
        }
    }

    const T& front() const
    {
        return get(0);
    }

    const T& back() const
    {
        return get(m_used - 1);
    }

private:
    const T& get(size_t index) const
    {
        if (empty())
        {
            throw std::length_error("empty list access");
        }
        else if (index > m_used - 1)
        {
            throw std::length_error("invalid list item access");
        }
        else
        {
            auto count = 0;
            auto temp = m_pItemFront;
            while (count < index)
            {
                temp = temp->next;
                ++count;
            }
            return *temp->m_pT;
        }
    }
};

template<class T>
class List
{
public:
    List() = default;
    ~List() = default;
    List(const List&) = delete;
    List(List&&) = delete;
    List& operator=(const List&) = delete;
    List& operator=(List&&) = delete;

    List(std::initializer_list<T> args)
    {
        for (auto& t : args)
        {
            push_back(t);
        }
    }

    const size_t size() const { return impl.m_used; }

    void push_front(const T& t)
    {
        impl.push_front(t);
    }

    void push_back(const T& t)
    {
        impl.push_back(t);
    }
    
    const T& front() const
    {
        return impl.front();
    }

    const T& back() const
    {
        return impl.back();
    }

    void pop_front()
    {
        impl.pop_front();
    }

    void pop_back()
    {
        impl.pop_back();
    }

private:
    ListImpl<T> impl;
};

#endif