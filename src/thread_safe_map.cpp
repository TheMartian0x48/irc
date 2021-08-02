#include "thread_safe_map.hpp"

bool ThreadSafeMap::empty() {
  std::lock_guard<std::mutex> lock(mutex_);
  return mp_.empty();
}

int ThreadSafeMap::size() {
  std::lock_guard<std::mutex> lock(mutex_);
  return mp_.size();
}

std::shared_ptr<Client> ThreadSafeMap::find(const std::string& key) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto res = mp_.find(key);
  if (res == mp_.end()) return nullptr;
  return res->second;
}

bool ThreadSafeMap::insert(std::pair<std::string, std::shared_ptr<Client>> key_value) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto res = mp_.insert(key_value);
  return res.second;
}


void ThreadSafeMap::remove(std::string key) {
  std::lock_guard<std::mutex> lock(mutex_);
  mp_.erase(key);
}

// 
// ThreadSafeMap<std::string,std::shared_ptr<Client>>::~ThreadSafeMap() {
//   std::lock_guard<std::mutex> lock(mutex_);
//   mp_.clear();
// }