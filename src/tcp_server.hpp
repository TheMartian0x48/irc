#ifndef IRC_SRC_TCP_SERVER_HPP_
#define IRC_SRC_TCP_SERVER_HPP_

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "global.hpp"
#include "server.hpp"

class TcpServer {
 private:
  int server_fd_;
  std::string host_address_;
  std::string host_name_;
  std::string port_;

 public:
  TcpServer(const std::string &, const std::string &);
  ~TcpServer();
  void Start();
  void Accept();

 private:
  void CreateSocket();
  std::string GetCurrentDate();
  void Listen(int);
  void InitialiseHint(struct addrinfo *);
  void InitialiseServer();
  struct addrinfo *GetAddresses(struct addrinfo *);
  void CreateSocketAndBind(struct addrinfo *);
  bool IsSocketCreationSuccessfulFor(struct addrinfo *);
  std::string GetHostAddress(struct addrinfo *);
  std::string GetHostAddress(struct sockaddr_storage *);
  void *GetInAddr(const struct sockaddr *);
  void CreateClientThread(int, std::string &);
};

#endif  // IRC_SRC_TCP_SERVER_HPP_