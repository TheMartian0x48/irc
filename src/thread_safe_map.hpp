#ifndef IRC_SRC_THREAD_SAFE_MAP_HPP_
#define IRC_SRC_THREAD_SAFE_MAP_HPP_

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

template<class KEY, class VALUE>
class ThreadSafeMap {
 private:
  std::unordered_map<KEY, VALUE> mp_;
  mutable std::mutex mutex_;

 public:
  ThreadSafeMap() = default;
  ~ThreadSafeMap();
  bool empty();
  int size();
  VALUE find(const KEY &);
  bool insert(std::pair<KEY, VALUE>);
  void remove(KEY);
};

#endif  // IRC_SRC_THREAD_SAFE_MAP_HPP_
