#ifndef THREAD_H
#define THREAD_H

#include <functional>
#include <thread>
#include <vector>

class Threads {

public:
    static void runThreads(int listSize, int numOfThreads, std::function<void(int, int)> worker) {
        std::vector<std::thread> threads;
        int chunkSize = listSize / numOfThreads;
        for (int i = 0; i < numOfThreads; ++i) {
            int start = i * chunkSize;
            int end = (i == numOfThreads - 1) ? listSize : start + chunkSize;
            threads.emplace_back(worker, start, end);
        }

        for (auto& t : threads) {
            t.join();
        }
    }
};




#endif //THREAD_H
