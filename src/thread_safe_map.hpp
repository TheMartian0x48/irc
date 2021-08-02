#ifndef IRC_SRC_THREAD_SAFE_MAP_HPP_
#define IRC_SRC_THREAD_SAFE_MAP_HPP_

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "client.hpp"

class ThreadSafeMap {
 private:
  std::unordered_map<std::string, std::shared_ptr<Client>> mp_;
  mutable std::mutex mutex_;

 public:
  ThreadSafeMap() = default;
  // ~ThreadSafeMap();
  bool empty();
  int size();
  std::shared_ptr<Client> find(const std::string &);
  bool insert(std::pair<std::string, std::shared_ptr<Client>>);
  void remove(std::string);
};

#endif  // IRC_SRC_THREAD_SAFE_MAP_HPP_
