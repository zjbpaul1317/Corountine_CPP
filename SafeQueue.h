#pragma once

#include <queue>
#include <mutex>

template <typename T>
class SafeQueue{
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;

public:
    SafeQueue() {}
    SafeQueue(SafeQueue &other) {}
    ~SafeQueue() {}

    //队列是否为空
    bool empty()
    {
        std::unique_lock<std::mutex> lock(m_mutex); //互斥信号变量加锁，防止m_queue被改变

        return m_queue.empty();
    }

    int size()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    //队列添加元素
    void enqueue(T& t)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(t);
    }

    //队列取出元素
    bool dequeue(T& t)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if(m_queue.empty())  return false;
        
        t = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

};
