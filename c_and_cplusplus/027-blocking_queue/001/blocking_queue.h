#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <deque>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue
{
public:
    BlockingQueue() {}
    ~BlockingQueue() {}

    void put(const T& x) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push_back(x);
        notEmpty_.notify_one();
    }

    T take() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty()) {
            notEmpty_.wait(lock);
        }
        T front(queue_.front());
        queue_.pop_front();
        return front;
    }

    size_t size() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.size();
    }

private:
    mutable std::mutex mutex_;
    std::deque<T> queue_;
    std::condition_variable notEmpty_;
};


#endif  // BLOCKING_QUEUE_H
