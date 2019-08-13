#include <iostream>
#include <thread>
#include <chrono>
#include "blocking_queue.h"

BlockingQueue<int> blockingQueue;

void produce()
{
    int num = 0;
    for (;;) {
        blockingQueue.put(num++);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consume()
{
    for (;;) {
        int num = blockingQueue.take();
        std::cout << "take num: " << num << std::endl;
    }
}

int main()
{
    std::thread produce1(produce);
    std::thread produce2(produce);

    std::thread consume(consume);

    produce1.join();
    produce2.join();
    consume.join();

    return 0;
}