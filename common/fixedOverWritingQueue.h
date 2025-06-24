#pragma once
#include <climits>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <queue>
#include <stdexcept>

struct ClosedQueue: public std::runtime_error {
    ClosedQueue(): std::runtime_error("The queue is closed") {}
};

/*
 * Multiproducer/Multiconsumer Blocking Queue (MPMC) Not anymore....
 *
 * Presenting the new Fixed-Size Queue with overwrite/discard oldest policy!
 *
 * push() and pop().
 * Two additional methods, try_push() and try_pop() allow
 * non-blocking operations.
 *
 */

template <typename T, class C = std::deque<T> >
class QueueFixed {
private:
    std::queue<T, C> q;
    const unsigned int max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

public:
    QueueFixed(): max_size(2), closed(false) {}

    void push(T const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        if (q.size() >= this->max_size) {
            q.pop();
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
    }


    T pop() {
        std::unique_lock<std::mutex> lck(mtx);

        while (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            is_not_empty.wait(lck);
        }

        // if (q.size() == this->max_size) {
        //     is_not_full.notify_all();
        // }

        T const val = q.front();
        q.pop();

        return val;
    }

    size_t getSize() { return q.size(); }

    void close() {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw std::runtime_error("The queue is already closed.");
        }

        closed = true;
        is_not_empty.notify_all();
    }

private:
    QueueFixed(const QueueFixed&) = delete;
    QueueFixed& operator=(const QueueFixed&) = delete;
};
