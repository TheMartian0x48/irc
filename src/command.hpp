#ifndef IRC_SRC_COMMAND_HPP
#define IRC_SRC_COMMAND_HPP

#include <memory>
#include <string>
#include <vector>

#include "client.hpp"

bool IsValidNick(const std::string &);

class Command {
 protected:
  std::string prefix_, command_name_;
  std::vector<std::string> parameter_;
  virtual std::pair<bool, std::string> Validate() = 0;

 public:
  Command() = delete;
  Command(std::string &&, std::vector<std::string> &&);
  Command(std::string &&, std::string &&, std::vector<std::string> &&);
  virtual void SendReply(std::shared_ptr<Client>) = 0;
  std::string CommandName();
};

class Nick : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
  bool SetNickName(std::shared_ptr<Client>);
};

class User : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
  bool SetUserAndFullName(std::shared_ptr<Client>);
};

class Quit : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
};

class Privmsg : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
};

class Notice : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
};

class Ping : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
};

class Pong : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
};

class Motd : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
};

class Lusers : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
};

class Whois : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
};

class Unknown : public Command {
 private:
  std::pair<bool, std::string> Validate();

 public:
  using Command::Command;
  void SendReply(std::shared_ptr<Client>);
};
#endif  // IRC_SRC_COMMAND_HPP
