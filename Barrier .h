//
// Created by Moroz on 23.01.2018.
//

#ifndef GAMEOFLIFE_1_BARRIER_H
#define GAMEOFLIFE_1_BARRIER_H

#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

using std::condition_variable;
class Barrier {
    const unsigned int threadCount;
    std::atomic<unsigned int>threadsWaiting;
    condition_variable waitVariable;
    std::mutex mutex;
    condition_variable & externalWaitVariable;
public:
    Barrier(unsigned int n, condition_variable & externalWaitVariable_) : threadCount(n),
                                                                          externalWaitVariable(externalWaitVariable_){
        threadsWaiting = 0;
    }
    Barrier(const Barrier &) = delete;
    void wait() {
        if (threadsWaiting.fetch_add(1) >= threadCount - 1) {
            externalWaitVariable.notify_all();
        }
        else {
            std::unique_lock<std::mutex> lock(mutex);
            waitVariable.wait(lock);
        }
    }
    void continueExrcution() {
        waitVariable.notify_all();
        threadsWaiting.store(0);
    }
};

#endif //GAMEOFLIFE_1_BARRIER_H
