#include "error.hpp"

/*******************************************************
See RFC 2812 section 5.2
Except for Quit() function, implementation follow
RFC with any modification
*******************************************************/

std::string IrcError::NoSuchNick(const std::string &nick) {
  return {"401 " + nick + " :No such nick/channer\r\n"};
}

std::string IrcError::NoSuchServer(const std::string &server_name) {
  return {"402 " + server_name + " :No such server\r\n"};
}

std::string IrcError::NoRecipient(const std::string &command) {
  return {"411 :No recipient given " + command + "\r\n"};
}

std::string IrcError::NoTextToSend() { return {"412 :No text to send\r\n"}; }

std::string IrcError::UnknownCommand(const std::string &command) {
  return {"421 " + command + " :Unknown command\r\n"};
}
std::string IrcError::NoMotd() { return {"422 :MOTD File is missing\r\n"}; }

std::string IrcError::NoNickNameGiven() { return {"431 :No nickname given\r\n"}; }

std::string IrcError::ErroneusNickName(const std::string &nick) {
  return {"432 " + nick + " :Erroneous nickname\r\n"};
}

std::string IrcError::NickNameInUse(const std::string &nick) {
  return {"433 " + nick + " :Nickname is aleardy in use\r\n"};
}

std::string IrcError::NotRegistered() { return {"451 :You have not registered\r\n"}; }

std::string IrcError::NeedMoreParams(const std::string &command) {
  return {"461 " + command + " :Not enough parameters\r\n"};
}

std::string IrcError::AlreadyRegistred() {
  return {"462 :Unauthorized command (already registered)\r\n"};
}

// Todo
std::string IrcError::Quit() { return {"Closing Link: \r\n"}; }

