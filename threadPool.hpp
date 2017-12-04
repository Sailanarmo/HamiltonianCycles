#ifndef THREAD_POOL
#define THREAD_POOL

#include "threadSafeQueue.hpp"
#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class ThreadPool
{
public:
  using func = std::function<void(void)>;
  ThreadPool(int n) : queue(), pool(n), hasItem(), itemMutex(), done(false), tasks(0) {}

  ~ThreadPool()
  {
    for (auto& t : pool) t.join();
  }

  void post(func f)
  {
    queue.enqueue(f);
    hasItem.notify_one();
    std::lock_guard<std::mutex> lock(m_task);
    ++tasks;
  }

  void start()
  {
    for (auto& t : pool) t = std::thread([&]() { this->run(); });
  }

  void stop()
  {
    done = true;
    hasItem.notify_all();
  }

private:
  TSQ<func> queue;
  std::vector<std::thread> pool;
  std::condition_variable hasItem;
  std::mutex itemMutex;
  std::mutex m_task;
  std::atomic<bool> done;
  int tasks;

  void run()
  {
    while (!done)
    {
      func task;
      if (queue.dequeue(task))
      {
        task();
        std::lock_guard<std::mutex> lock(m_task);
        --tasks;
        if (tasks <= 0) stop();
      }
      if (done) return;
    }
  }
};

#endif
