#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <mutex>
#include <queue>

template <typename T>
class TSQ
{
public:
  void enqueue(T t)
  {
    std::lock_guard<std::mutex> lock(m);
    q.push(t);
  }

  /*
template <typename Ts..>
void emplace(..Ts args)
{
q.emplace_back(..args);
}
  */

  bool dequeue(T &result)
  {
    std::lock_guard<std::mutex> lock(m);
    if (q.empty()) return false;
    result = q.front();
    q.pop();
    return true;
  }

private:
  std::queue<T> q;
  std::mutex m;
};

#endif
