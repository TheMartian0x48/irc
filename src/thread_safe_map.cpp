#include "thread_safe_map.hpp"

template<class KEY, class VALUE>
bool ThreadSafeMap<KEY, VALUE>::empty() {
  std::lock_guard<std::mutex> lock(mutex_);
  return mp_.empty();
}

template<class KEY, class VALUE>
int ThreadSafeMap<KEY, VALUE>::size() {
  std::lock_guard<std::mutex> lock(mutex_);
  return mp_.size();
}

template<class KEY, class VALUE>
VALUE ThreadSafeMap<KEY, VALUE>::find(const KEY& key) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto res = mp_.find(key);
  if (res == mp_.end()) return nullptr;
  return res->second;
}

template<class KEY, class VALUE>
bool ThreadSafeMap<KEY, VALUE>::insert(std::pair<KEY, VALUE> key_value) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto res = mp_.insert(key_value);
  return res.second;
}


template<class KEY, class VALUE>
void ThreadSafeMap<KEY, VALUE>::remove(KEY key) {
  std::lock_guard<std::mutex> lock(mutex_);
  mp_.erase(key);
}
