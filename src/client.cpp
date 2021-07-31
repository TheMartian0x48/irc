#include "client.hpp"

#include <unistd.h>

#include <iostream>

#include "global.hpp"
#include "irc_exception.hpp"
#include "server.hpp"

extern ThreadSafeMap<std::string, std::shared_ptr<Client>> active_users;

Client::Client(const std::string &host, int fd) {
  host_ = host;
  fd_ = fd;
  tcp_writer_ = TcpWriter();
}

Client::~Client() {
  active_users.remove(nick_);
  // delete from active_users
  // so that no other can request for sending message
  Send({});
  // than send 0 byte data because
  // those already waiting for sending
  // will finish by now
  // then boom delete it
  close(fd_);
}

void Client::SetNick(const std::string &nick) { nick_ = nick; }

void Client::SetUser(const std::string &user) { user_ = user; }

void Client::SetFullName(const std::string &full_name) {
  full_name_ = full_name;
}

void Client::SetUserMode(const std::string &user_mode) {
  user_mode_ = user_mode;
}

std::string Client::GetNick() const { return nick_; }

std::string Client::GetUser() const { return user_; }

std::string Client::GetFullName() const { return full_name_; }

std::string Client::GetUserMode() const { return user_mode_; }

std::string Client::GetHost() const { return host_; }

std::string Client::GetFullClientId() const {
  return nick_ + "!" + user_ + "@" + host_;
}

bool Client::Send(const std::string &message) {
  std::lock_guard<std::mutex> lock(mutex_);
  try {
    tcp_writer_.Write(fd_, message);
    return true;
  } catch (const IrcException &e) {
    std::cerr << e.what() << std::endl;
  }
  return false;
}
