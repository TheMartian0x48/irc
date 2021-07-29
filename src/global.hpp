#ifndef IRC_SRC_GLOBAL_HPP
#define IRC_SRC_GLOBAL_HPP

#include <memory>
#include <string>

#include "client.hpp"
#include "server.hpp"
#include "thread_safe_map.hpp"

extern Server irc_server;
extern ThreadSafeMap<std::string, std::shared_ptr<Client>> active_users;

#endif  // IRC_SRC_GLOBAL_HPP_
