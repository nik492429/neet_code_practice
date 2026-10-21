#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <iostream>
#include <vector>


class BlockingQueue
{
public:    
    void Push(int val);
    int Pop();

private:
    std::queue<int> Queue;
    std::mutex Mutex;
    std::condition_variable Condition;
};

void BlockingQueue::Push(int val)
{
    std::lock_guard<std::mutex> m(Mutex);
    Queue.push(val);
    Condition.notify_all();
}

int BlockingQueue::Pop()
{
    std::unique_lock<std::mutex> lock(Mutex);
    Condition.wait(lock, [this]{return !Queue.empty();});
    int val = Queue.front();
    Queue.pop();
    return val;         
}

BlockingQueue Q;

void ProducerThread(int scaleFactor)
{
    for(int i=1; i<=5; i++)
    {
        Q.Push(scaleFactor*i);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ConsumerThread()
{
    while(true)
    {
        int val = Q.Pop();
        std::cout << "val = " << val << std::endl; 
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

int main()
{

    std::thread t1(ProducerThread, 1);
    std::thread t2(ProducerThread, 2);
    std::thread t3(ProducerThread, 3);
    std::thread t4(ConsumerThread);
    std::thread t5(ConsumerThread);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    return 0;
}