#ifndef IRC_SRC_CLIENT_HPP_
#define IRC_SRC_CLIENT_HPP_

#include <mutex>
#include <string>

#include "tcp_writer.hpp"

class Client {
 private:
  std::string nick_;
  std::string full_name_;
  std::string user_;
  std::string user_mode_;
  std::string host_;
  int fd_;
  TcpWriter tcp_writer_;
  mutable std::mutex mutex_;

 public:
  Client() = delete;
  Client(const std::string &, const std::string &, const std::string &,
         const std::string &, const std::string &, int);
  Client(const Client &) = delete;
  Client(Client &&) = delete;
  Client &operator=(const Client &) = delete;
  Client &operator=(Client &&) = delete;
  ~Client();

  void SetNick(const std::string &);
  void SetUser(const std::string &);
  void SetFullName(const std::string &);
  void SetUserMode(const std::string &);

  std::string GetNick() const;
  std::string GetUser() const;
  std::string GetFullName() const;
  std::string GetUserMode() const;
  std::string GetHost() const;
  std::string GetFullClientId() const;

  void Send(const std::string &);
};

#endif  // IRC_SRC_CLIENT_HPP_
