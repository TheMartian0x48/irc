#include "server.hpp"

Server::Server(const std::string &version, const std::string &password,
               const std::string &info) {
  name_ = host_ = creation_date_ = {};
  version_ = version;
  password_ = password;
  info_ = info;
}
std::string Server::GetHost() const { return host_; }

std::string Server::GetName() const { return name_; }

std::string Server::GetCreationDate() const { return creation_date_; }

std::string Server::GetVersion() const { return version_; }

std::string Server::GetInfo() const { return info_; }

void Server::SetHost(const std::string &host) { host_ = host; }

void Server::SetName(const std::string &server_name) { name_ = server_name; }

void Server::SetCreationDate(const std::string &creation_date) {
  creation_date_ = creation_date;
}