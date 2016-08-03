#pragma once

#include <stdexcept>
#include <initializer_list>

template<class T>    
struct ListItem
{
    ListItem(const T& t, ListItem* next, ListItem* prev)
        : m_pT(new T(t))
        , m_next(next)
        , m_prev(prev)
        { }

    ~ListItem()
    {
        m_next = nullptr;
        m_prev = nullptr;
        delete m_pT;
    }

    T* m_pT;
    ListItem* m_next;
    ListItem* m_prev;
};

template<class T>
class List
{
public:
    List() = default;
    List(const List&) = delete;
    List(List&&) = delete;
    List& operator=(const List&) = delete;
    List& operator=(List&&) = delete;
    
    ~List()
    {
        auto item = m_pListItemFront;
        while (item)
        {
            item = m_pListItemFront->m_next;
            delete m_pListItemFront;
            m_pListItemFront = item;
        }
    }

    size_t size() const { return m_size; }
    bool empty() const { return (size() == 0); }

    List(std::initializer_list<T> args)
    {
        for (auto& t : args)
        {
            push_back(t);
        }
    }

    void push_front(const T& t)
    {
        if (empty())
        {
            m_pListItemFront = m_pListItemLast = 
                new ListItem<T>(t, nullptr, nullptr);
            ++m_size;
        }
        else
        {
            auto pNew = new ListItem<T>(t, m_pListItemFront, nullptr);
            m_pListItemFront->m_prev = pNew;
            m_pListItemFront = pNew;
            ++m_size;
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
            auto pNew = new ListItem<T>(t, nullptr, m_pListItemLast);
            m_pListItemLast->m_next = pNew;
            m_pListItemLast = pNew;
            ++m_size;
        }
    }
    
    const T& front() const
    {
        if (empty())
        {
            throw std::length_error("empty list pop front");
        }
        return *m_pListItemFront->m_pT;
    }

    const T& back() const
    {
        if (empty())
        {
            throw std::length_error("empty list pop front");
        }
        return *m_pListItemLast->m_pT;
    }

    void pop_front()
    {
        if (empty())
        {
        }
        else
        {
            auto pToRemove = m_pListItemFront;
            auto pNext = m_pListItemFront->m_next;
            if (pNext)
            {
                pNext->m_prev = nullptr;
                m_pListItemFront = pNext;
            }
            else
            {
                m_pListItemFront = m_pListItemLast = nullptr;
            }
            --m_size;
            delete pToRemove;
        }
    }

    void pop_back()
    {
        if (empty())
        {
        }
        else
        {
            auto pToRemove = m_pListItemLast;
            auto pPrev = m_pListItemLast->m_prev;
            if (pPrev)
            {
                pPrev->m_next = nullptr;
                m_pListItemLast = pPrev;
            }
            else
            {
                m_pListItemFront = m_pListItemLast = nullptr;
            }
            --m_size;
            delete pToRemove;
        }
    }

private:
    ListItem<T>* m_pListItemFront {nullptr};
    ListItem<T>* m_pListItemLast {nullptr};
    size_t m_size {0};
};