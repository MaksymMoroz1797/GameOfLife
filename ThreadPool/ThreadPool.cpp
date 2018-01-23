//
// Created by Moroz on 23.01.2018.
//

#include <chrono>
#include "ThreadPool.h"

ThreadPool::ThreadPool():
            workers(),
            taskQueue(),
            taskCount(0u),
            mutex(),
            condition(),
            stop(false) {}

ThreadPool::ThreadPool(size_t threads): ThreadPool() {
    initializeWithThreads(threads);
}

ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all();
    for ( std::thread& w: workers ) {
        w.join();
    }
}

void ThreadPool::initializeWithThreads(size_t threads) {
    for (int i = 0; i < threads; i++) {
        workers.emplace_back( [this]() -> void {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock( mutex );
                    condition.wait( lock, [this]() -> bool {
                        return !taskQueue.empty() || stop;
                    });

                    if ( stop && taskQueue.empty() ) {
                        return;
                    }

                    task = std::move( taskQueue.front() );
                    taskQueue.pop();
                }
                task();
                taskCount--;
            }
        });
    }
}

void ThreadPool::schedule(const std::function<void()>& task) {
    {
        std::unique_lock<std::mutex> lock( mutex );
        taskQueue.push( task );
    }
    taskCount++;
    condition.notify_one();
}

void ThreadPool::wait() const {
    while (taskCount != 0u) {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}
