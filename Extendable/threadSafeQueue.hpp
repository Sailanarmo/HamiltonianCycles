#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <atomic>
#include <chrono>
#include <mutex>
#include <queue>
#include <thread>
#include <limits>

using namespace std::chrono_literals;

template <typename T>
class TSQ
{
public:
  TSQ(int maxs = std::numeric_limits<int>::max()) : qsize(0), more(true), maxsize(maxs) {}
  void enqueue(T t)
  {
    while (qsize > maxsize)
    {
      std::this_thread::sleep_for(5s);
    }

    {
      std::lock_guard<std::mutex> lock(m);
      q.push(t);
    }
    ++qsize;
  }

  /*
template <typename Ts..>
void emplace(..Ts args)
{
q.emplace_back(..args);
}
  */

  bool dequeue(T& result)
  {
    {
      std::lock_guard<std::mutex> lock(m);
      if (q.empty()) return false;
      result = q.front();
      q.pop();
    }
    --qsize;
    return true;
  }

  int size() { return qsize; }
  void done() { more = false; }
  bool hasMore() { return more; }

private:
  std::atomic<int> qsize;   // current size of the queue
  std::atomic<bool> more;   // more to be read from stdin
  std::atomic<int> maxsize; // maximum size of the queue
  std::queue<T> q;
  std::mutex m;
};

#endif
