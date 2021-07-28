#include "tcp_server.hpp"
#include "server.hpp"

#include <ctime>

extern Server irc_server;

TcpServer::TcpServer(const std::string &host_name, const std::string &port) {
  host_name_ = host_name;
  host_address_ = {};
  port_ = port;
}

TcpServer::~TcpServer() {
  close(server_fd_);
}

void TcpServer::Start() {
  CreateSocket();
  InitialiseServer();
  Listen(10);
}

void TcpServer::CreateSocket() {
  struct addrinfo hint;
  InitialiseHint(&hint);
  auto addresses = GetAddrresses(&hint);
  CreateSocketAndBind(addresses);
  freeaddrinfo(addresses);
}

void TcpServer::InitialiseHint(struct addrinfo *hint) {
  memset(hint, 0, sizeof(*hint));
  hint->ai_flags = AI_PASSIVE;
  hint->ai_family = AF_UNSPEC;
  hint->ai_socktype = SOCK_STREAM;
}

struct addrinfo *TcpServer::GetAddrresses(struct addrinfo *hint) {
  struct addrinfo *addresses;
  int has_error =
      getaddrinfo(host_name_.c_str(), port_.c_str(), hint, &addresses);
  if (has_error) {
    std::cerr << "getaddrinfo : " << gai_strerror(has_error) << std::endl;
    exit(1);
  }
  return addresses;
}

void TcpServer::CreateSocketAndBind(struct addrinfo *addresses) {
  auto address = addresses;
  while (address != nullptr &&
         IsSocketCreationSuccessfulFor(address) == false) {
    address = address->ai_next;
  }
  if (address == nullptr) {
    freeaddrinfo(addresses);
    std::cerr << "TCP listen error for " << host_name_ << ":" << port_
              << std::endl;
    exit(1);
  }
  SetHostAddress(address);
}

bool TcpServer::IsSocketCreationSuccessfulFor(struct addrinfo *address) {
  server_fd_ =
      socket(address->ai_family, address->ai_socktype, address->ai_protocol);
  if (server_fd_ < 0) return false;
  if (bind(server_fd_, address->ai_addr, address->ai_addrlen) == 0) return true;
  close(server_fd_);
  return false;
}

void TcpServer::SetHostAddress(struct addrinfo *address) {
  char host_address[INET6_ADDRSTRLEN];
  inet_ntop(address->ai_family, GetInAddr((struct sockaddr *)address->ai_addr),
            host_address, sizeof host_address);
  host_address_ = std::string(host_address);
}

void *TcpServer::GetInAddr(const struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void TcpServer::InitialiseServer() {
  irc_server.SetCreationDate(GetCurrentDate());
  irc_server.SetHost(host_address_);
  if (host_name_.empty())
    irc_server.SetName(host_address_);
  else
    irc_server.SetName(host_name_);
}

std::string TcpServer::GetCurrentDate() {
  time_t now = time(0);
  std::string time_of_creation = std::ctime(&now);
  return time_of_creation.substr(0, time_of_creation.size() - 1);
}

void TcpServer::Listen(int backlog) {
  char *ptr = getenv("LISTENQ");
  if (ptr != nullptr) backlog = atoi(ptr);
  if (listen(server_fd_, backlog) < 0) {
    std::cerr << "Listen() : unable to listen" << std::endl;
    exit(1);
  }
}
