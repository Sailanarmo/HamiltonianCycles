#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <atomic>
#include <mutex>
#include <queue>

template <typename T>
class TSQ
{
public:
  TSQ() : qsize(0), more(true) {}
  void enqueue(T t)
  {
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

private:
  std::atomic<int> qsize;
  std::atomic<bool> more; //more to be read from stdin
  std::queue<T> q;
  std::mutex m;
};

#endif
