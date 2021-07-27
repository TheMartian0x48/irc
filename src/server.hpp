#ifndef IRC_SRC_SERVER_HPP_
#define IRC_SRC_SERVER_HPP_

#include <string>

class Server {
 private:
  std::string name_;
  std::string host_;
  std::string creation_date_;
  std::string version_;
  std::string password_;
  std::string info_;

 public:
  Server() = default;
  Server(const std::string &, const std::string &, const std::string &);
  std::string GetHost() const;
  std::string GetName() const;
  std::string GetCreationDate() const;
  std::string GetVersion() const;
  std::string GetInfo() const;
  void SetHost(const std::string &);
  void SetName(const std::string &);
  void SetCreationDate(const std::string &);
};

#endif  // IRC_SRC_SERVER_HPP_
