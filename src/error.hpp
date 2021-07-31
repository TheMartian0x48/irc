#ifndef IRC_SRC_ERROR_HPP_
#define IRC_SRC_ERROR_HPP_

#include <string>

/*******************************************************
See RFC 2812 section 5.2
Except for Quit() function, implementation follow
RFC with any modification
*******************************************************/

namespace IrcError{

std::string NoSuchNick(const std::string &nick) {
  return {"401 " + nick + " :No such nick/channer\r\n"};
}

std::string NoSuchServer(const std::string &server_name) {
  return {"402 " + server_name + " :No such server\r\n"};
}

std::string NoRecipient(const std::string &command) {
  return {"411 :No recipient given " + command + "\r\n"};
}

std::string NoTextToSend() { return {"412 :No text to send\r\n"}; }

std::string UnknownCommand(const std::string &command) {
  return {"421 " + command + " :Unknown command\r\n"};
}
std::string NoMotd() { return {"422 :MOTD File is missing\r\n"}; }

std::string NoNickNameGiven() { return {"431 :No nickname given\r\n"}; }

std::string ErroneusNickName(const std::string &nick) {
  return {"432 " + nick + " :Erroneous nickname\r\n"};
}

std::string NickNameInUse(const std::string &nick) {
  return {"433 " + nick + " :Nickname is aleardy in use\r\n"};
}

std::string NotRegistered() { return {"451 :You have not registered\r\n"}; }

std::string NeedMoreParams(const std::string &command) {
  return {"461 " + command + " :Not enough parameters\r\n"};
}

std::string AlreadyRegistred() {
  return {"462 :Unauthorized command (already registered)\r\n"};
}

// Todo
std::string Quit() { return {"Closing Link: \r\n"}; }
}
#endif  // IRC_SRC_ERROR_HPP_
