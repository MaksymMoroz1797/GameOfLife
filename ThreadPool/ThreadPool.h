//
// Created by Moroz on 23.01.2018.
//

#ifndef GAMEOFLIFE_1_THREADPOOL_H
#define GAMEOFLIFE_1_THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>

class ThreadPool {
public:
    ThreadPool();
    ThreadPool( size_t threads );
    ~ThreadPool();

    void initializeWithThreads( size_t threads );

    void schedule( const std::function<void()>& );

    void wait() const;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> taskQueue;
    std::atomic_uint taskCount;
    std::mutex mutex;
    std::condition_variable condition;
    std::atomic_bool stop;
};

#endif //GAMEOFLIFE_1_THREADPOOL_H
